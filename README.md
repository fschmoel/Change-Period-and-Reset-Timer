All diese Dateien können Sie, in Ihrem Eclipse-Workspace implementieren. 
Schauen Sie das sie jedes Projekt fehlerfrei kompilieren können. 
Der eigentliche Programmcode ist im Ordner free-rtos-demo --> src, die Datei lautet test.cpp.
Nachdem Sie das Projekt free-rtos-demo kompiliert haben, bildet sich eine hex-Datei im Ordner Release. 
Diese hex-Datei können sie mithilfe des avrdude auf Ihrem Arduino laden. 
Dazu benötigen Sie eine Eingabeaufforderung, die Sie in das Terminal einfügen können. Diese lautet: 

avrdude -v -P /dev/ttyUSB0 -c USBasp -p m328p -u -U flash:w:eclipse-workspace/free-rtos-demo/Release/free-rtos-demo.hex

Nachdem dies erfolgreich war, müssen Sie sich die serielle Kommunikation des Arduinos anschauen.
Dies erfolgt über einen seriellen Monitor. Über minicom wäre es eine Möglichkeit, sich über das Terminal die serielle Kommunikation anzuschauen. 
Fügen sie folgende Kommandozeile in Ihr Terminal ein: 

minicom -D /dev/ttyUSB0 -b 115200

Jetzt sehen Sie im Terminal, wie der Timer des Arduinos startet.
