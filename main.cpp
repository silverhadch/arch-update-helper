#include <QAction>
#include <QApplication>
#include <QDir>
#include <QFile>
#include <QIcon>
#include <QMenu>
#include <QProcess>
#include <QStringList>
#include <QSystemTrayIcon>
#include <QTextStream>
#include <QThread> // <-- Add this line
#include <QTimer>

QString terminal = "kitty"; // Default terminal
QString aurHelper = "yay"; // Default AUR helper
QString configFilePath = QDir::homePath() + "/.config/arch-update-helper";
int updatesAvailable = 0; // Initial state: no updates available

void readConfig() {
  QFile configFile(configFilePath);
  if (configFile.exists() &&
      configFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
    QTextStream in(&configFile);
    while (!in.atEnd()) {
      QString line = in.readLine();
      // Only read valid lines, and skip comments
      if (!line.isEmpty() && !line.startsWith("#")) {
        QStringList parts = line.split("=");
        if (parts.size() == 2) {
          QString key = parts[0].trimmed();
          QString value = parts[1].trimmed();
          if (key == "terminal") {
            terminal = value;
          } else if (key == "aur_helper") {
            aurHelper = value;
          }
        }
      }
    }
    configFile.close();
  }
#ifdef DEBUG
  else {
    qDebug() << "Config file not found or could not be opened. Using defaults.";
  }
#endif
}

int checkForUpdates() {
#ifdef DEBUG
  qDebug() << "Checking for updates...";
#endif
  QProcess process;
  process.start(aurHelper, QStringList() << "-Qu");
  process.waitForFinished();
  QString output = process.readAllStandardOutput();
#ifdef DEBUG
  qDebug() << aurHelper << " -Qu output:\n" << output;
#endif

  if (!output.isEmpty()) {
    updatesAvailable = 1; // Updates are available
#ifdef DEBUG
    qDebug() << "Updates available!";
#endif
  } else {
    updatesAvailable = 0; // No updates
#ifdef DEBUG
    qDebug() << "No updates available.";
#endif
  }
  return updatesAvailable;
}

void updateTrayIcon(QSystemTrayIcon *trayIcon) {
  if (updatesAvailable == 1) {
    trayIcon->setIcon(QIcon::fromTheme("system-software-update"));
    trayIcon->showMessage("Updates Available",
                          "Left-click the update icon to update your system.",
                          QSystemTrayIcon::Information, 5000);
  } else {
    trayIcon->setIcon(QIcon::fromTheme("package-x-generic"));
  }
}

bool isProcessRunning(const QString &processName) {
  QProcess process;
  process.start("pgrep", QStringList() << "-f" << processName);
  process.waitForFinished();
  QString output = process.readAllStandardOutput().trimmed();
  return !output
              .isEmpty(); // If the output is not empty, the process is running
}

int main(int argc, char *argv[]) {
  QApplication app(argc, argv);

  // Check if running in test mode
  bool isTestMode = (argc > 1 && QString(argv[1]) == "--test");

  readConfig();

  // Create a tray icon and menu
  QSystemTrayIcon *trayIcon = new QSystemTrayIcon();
  trayIcon->setIcon(
      QIcon::fromTheme("package-x-generic")); // Default icon for "no updates"

  QMenu *trayMenu = new QMenu();

  // Action to check for updates
  QAction *checkUpdatesAction = new QAction("Check for Updates");
  trayMenu->addAction(checkUpdatesAction);

  // Action to quit the application
  QAction *quitAction = new QAction("Quit");
  trayMenu->addAction(quitAction);

  trayIcon->setContextMenu(trayMenu);
  trayIcon->show();

  // Handling real mode or test mode
  if (isTestMode) {
#ifdef DEBUG
    qDebug() << "Running in testing mode! Simulating updates available.";
#endif
    updatesAvailable = 1;     // Simulate updates available
    updateTrayIcon(trayIcon); // Show the "updates available" icon
  } else {
#ifdef DEBUG
    qDebug() << "Running in real mode!";
#endif
    checkForUpdates();        // Check for updates at the start
    updateTrayIcon(trayIcon); // Set the icon based on available updates
  }

  // When the user clicks the tray icon
  QObject::connect(
      trayIcon, &QSystemTrayIcon::activated,
      [&](QSystemTrayIcon::ActivationReason reason) {
        if (reason == QSystemTrayIcon::Trigger) {
#ifdef DEBUG
          qDebug() << "Tray icon clicked. Launching terminal and AUR helper...";
#endif
          QProcess *process = new QProcess();
          process->startDetached(terminal, QStringList() << "-e" << aurHelper);
#ifdef DEBUG
          qDebug()
              << "Waiting for the terminal and AUR helper process to finish...";
#endif

          // Watch for the terminal and AUR helper process to finish
          while (isProcessRunning(terminal) || isProcessRunning(aurHelper)) {
#ifdef DEBUG
            qDebug()
                << "Process(es) still running, waiting for them to finish...";
#endif
            QThread::sleep(1); // Sleep 1 second to check again
          }

#ifdef DEBUG
          qDebug() << "Terminal and AUR helper process finished.";
#endif
          checkForUpdates(); // Check for updates once the process finishes
          updateTrayIcon(trayIcon); // Update icon based on update status
        }
      });

  // When the user clicks the "Check for Updates" action
  QObject::connect(checkUpdatesAction, &QAction::triggered, [&]() {
#ifdef DEBUG
    qDebug() << "Check for updates clicked!";
#endif
    QProcess::startDetached(terminal, QStringList() << "-e" << aurHelper);
  });

  // When the user clicks the "Quit" action
  QObject::connect(quitAction, &QAction::triggered, &app, &QApplication::quit);

  // Timer to check for updates every 10 minutes (600 seconds)
  QTimer *updateTimer = new QTimer();
  QObject::connect(updateTimer, &QTimer::timeout, [&]() {
#ifdef DEBUG
    qDebug() << "Sleeping for 10 minutes, waiting for the next update check...";
#endif
    checkForUpdates();
    updateTrayIcon(trayIcon);
  });
  updateTimer->start(600000); // Check every 10 minutes

  return app.exec();
}
