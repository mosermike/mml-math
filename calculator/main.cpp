/**
 * : @author Mike Moser
 * : @date 22.05.2024
 * : @version 4
 * : @name calculator
 * : @file main.cpp
 * : 
 * : Version history:
 * : @version  4     (22.05.2024) Big changes for the matrix calculations
 * : @version  3.0.4 (07.01.2024) Fixed some bugs
 * : @version  3.0.3 (27.01.2023) Determinantenberechnung korrigiert; Korrektur, wenn eine Matrix ohne Anfangs- bzw. Endklammer übergeben wird.
 * : @version  3.0.2 (06.09.2022) Atomare Masseneinheit hinzugefügt, logb todo gelöscht => einfach als log(x)/log(b) berechnen, Log Datei nur 0 löschen nach dem Komma
 * : @version  3.0.1 (04.03.2022) Bracket Problem gelöst (bracket check); arcsin, arccos, sqrt domain error hinzugefügt, grad <=> rad korrigiert
 * : @version  3.0   (17.09.2021) Komplette Operatoren überarbeitet und ein paar Fehler behoben.
 * : @version  2.5.5 (03.02.2021) Grad zu Radiant, Radiant zu Grad, arcsin, arccos, arctan hinzugefügt
 * : @version  2.5.4 (30.10.2020) Verbesserungen, Gauß-Verfahren korrigiert bei Nullspalte, logging verbessert, old_add reingemacht
 * : @version  2.5.3 (08.07.2020) Logging für Matrix
 * : @version  2.5.2 (30.04.2020) Fehlerüberarbeitung summation neu gemacht, da mittlerer Term ignoriert
 * : @version  2.5.1 (14.04.2020) Fehlerüberarbeitung
 * ; @version  2.5   (07.03.2020) Logdatei überarbeitet durch Klasse log
 * : @version  2.4   (22.12.2019) Kommentarfunktion für die logdatei
 * : @version  2.3   (10.08.2019) Logdatei implementiert mit Ausgabe über -l, --logfile
 * : @version  2.2   (14.03.2019) Physikalische Konstanten hinzugefügt, -u überarbeitet mit anstatt , , getArg implementiert
 * : @version  2.1   (27.02.2019) pos_bracket überarbeitet und verbessert, Klammerbehandlung hinzugefügt, --calculations erstellt, --cs mit alten Resultaten und ersetzen von o ohne -o bei --cs,
 * : 							  save_result als inline, calculations erstellt mit Übernahme von den Ergebnissen bei -cs
 * : @version  2.0   (22.02.2019) Funktion replace und add_oldresult, sqrt integriert, ^ integriert, si-präfixe, mehrere Variablen verwenden; log, ln, log2, logb, exp, sin, cos, tan integriert,
 * : 							  calculate erstellt, -t hinzugefügt
 * : @version  1.6   (17.02.2019) e Funktion hinzugefügt, exponentenfunktion durch pow ersetzt, if Bedingungen für pi und ki hinzugefügt
 * : @version  1.5   (10.12.2018) Pi Funktion hinzugefügt für basic_operations, sowie Verbesserungen von -s und -m, Übernahme der alten Werte, Variable x verwenden, mml::string integriert
 * : @version  1.4   (09.11.2018) basic_operations.hpp erstellt mit -s und -m
 * : @version  1.3   (01.11.2018) Grenzen angepasst, die erlaubt sind. Hat bei der Multiplikation 9 nicht erlaubt
 * : @version  1.2   (15.10.2018) Neue Funktion rechnen mit Exponenten zur Basis, Hilfeseite nach Muster, uintX_t angepasst
 * : @version  1.1   (22.05.2018) Ableiten einer einfachen Funktion
 * : @version  1.0   (21.05.2018)
 * :
 * :
 * : @details:
 * : Berechnung von verschiedenen Sachen mit der Konsole
 * : 
 * :
*/

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <iomanip>	// setprecision
#include <mml.hpp>
#include <mml-math.hpp>

#ifndef calc_log
#define calc_log 		"./calc.log"
#endif

// NOTE Rechner
// TODO Bruchform ausgeben
// TODO log(12) in -cs geht nicht (behoben, aber nur notlösung => works no?)
// TODO nachschauen welche Variablen gehen und welche nicht => Warnung ausgeben
// TODO grad in rad umrechner
// TODO Warnung wenn Buchstabe in Rechnung : rechnung -c asd
// TODO look at logb
// TODO Ausgaben werden gekürzt

// NOTE Matrix
// TODO Matrix old rechnung (bzw. in matrixform ausgeben temporär)
// TODO Matrixnorm
// TODO Skalarmultiplikation matrix
// TODO rechner -m "[0,0,1]*[[0,2,0],[3,0,2],[0,3,0]]"

/**
* @note Help Page
* @return None
* @author Mike Moser
*/
void help() {

	mml::help::header("Führt verschiedene Berechungen durch.");
	
	std::cout << "\tDieses Programm führt verschiedene Berechnungen durch abhängig von den Argumenten." << std::endl;
	std::cout << "\tBei der Verwendung von Klammern sind Anführunszeichen notwendig bei der Gleichung."	<< std::endl << std::endl;
	std::cout << "\tErforderliche Argumente für lange Optionen sind auch für kurze erforderlich." << std::endl;
	mml::shell::option("-a, --adjunct" , "Adjunkte einer Matrix berechnen. Mit -m Matrix übergeben");
	mml::shell::option("-c, --calculate" , "Gleichung lösen mit allen Operatoren.");
	mml::shell::option("-cs, --calculations" , "Mehrere verschiedene Gleichungen lösen mit allen Operatoren.");
	mml::shell::option("-d, --det" , "Determinante einer Matrix berechnen. Mit -m Matrix übergeben");
	mml::shell::option("    --grad" , "Ausgabe oder Angabe in Grad in Abhängigkeit des Operators.");
	mml::shell::option("-h, --help" , "Ausgabe dieser Hilfe.");
	mml::shell::option("-i, --inverse" , "Inverse einer Matrix berechnen. Mit -m Matrix übergeben");
	mml::shell::option("-k, --comment"  , "Kommentar in die Logdatei hinter Rechnung.");
	mml::shell::option("-l, --log"  , "Ausgabe der Logdatei.");
	mml::shell::option("-lr, --log_reset", "Zurücksetzen der Logdatei");
	mml::shell::option("-lb, --log_backup", "Backup der Logdatei");
	mml::shell::option("-m, --matrix" , "Multiplzieren und Addieren von Matrizen.Matrixform [[1.,Reihe],[2.,Reihe]]");
	mml::shell::option("-ml, --matrix-latex" , "Format in Latex. (Achtung Matrix endet und startet mit '|')");
	mml::shell::option("-t, --timer", "Ausgabe der Dauer der Berechnung");
	mml::shell::option("-tr, --transpose" , "Transponierte einer Matrix berechnen. Mit -m Matrix übergeben");
	mml::shell::option("-u" , "Wertzuweisung einer oder mehreren unbekannten Variable(n) mit Trennzeichen ':' in der Gleichung. z.B. -u x=2");
	mml::shell::chapter("Verfügbare Operationen:", true);
	mml::shell::option("+" , "Addition verschiedener Werte.");
	mml::shell::option("-" , "Subtrahieren verschiedener Werte.");
	mml::shell::option("*", "Multiplikation verschiedener Werte.");
	mml::shell::option("/" , "Dividieren von zwei Zahlen(alt).");
	mml::shell::option("//" , "Dividieren von mehreren Zahlen(alt).");
	mml::shell::option("d" , "Ableiten einer Funktion. Direkt als Parameter übergeben(alt).");
	mml::shell::option("^" , "Multiplizieren einer Basis zu einem Exponenten.");
	mml::shell::option("^(" , "Multiplizieren einer Basis zu einem Exponenten.");
	mml::shell::option("exp(x)" , "Berechnen von exp^(x).");
	mml::shell::option("sin(x)" , "sin berechnen von x.");
	mml::shell::option("cos(x)" , "cos berechnen von x.");
	mml::shell::option("tan(x)" , "tan berechnen von x.");
	mml::shell::option("arcsin(x)" , "arcsin berechnen von x.");
	mml::shell::option("arccos(x)" , "arccos berechnen von x.");
	mml::shell::option("arctan(x)" , "arctan berechnen von x.");
	mml::shell::option("ln(x)" , "logarithmus naturalis berechnen von x.");
	mml::shell::option("log(x)" , "10er Logarithmus berechnen von x.");
	mml::shell::option("log2(x)" , "2er Logarithmus berechnen von x.");
	mml::shell::option("logb(x)" , "Logarithmus zur Basis b berechnen von x.");
	mml::shell::option("sqrt(x)" , "Wurzel ziehen von x.");
	std::cout << std::endl;
	mml::shell::chapter("Optionen bei --calculations:",true);
	mml::shell::option("rx", "Verwendung des Ergebnisses von Gleichung x, rx wird in der neuen Gleichung ersetzt");
	std::cout << std::endl;
	mml::shell::chapter("Sonstiges:", true);
	std::cout << "\tVorhandene Konstanten: pi, exp,E , P_c, P_k, P_m, P_e, P_G, P_h, P_µ, P_NA, P_u" << std::endl;
	std::cout << "\tVorhandene Potenzen:   p, n, µ, m, k, M, G, T oder mit e" << std::endl << std::endl;

	mml::help::foot("3.0.4", "January", 2024);
}

int main(int argc, char **argv) {
	
	mml::shell::arg		args		(argc,argv);
	mml::Timer			time		;
	double				result		= 0;
	mml::string			matrix		= "";
	
	if(args.notArg("-t","--timer"))
		time.stop();
		
	if(args.size() == 1){
	
		mml::shell::letter("red");
		std::cout << "Fehlende Eingabe der gewünschten Operation!" << std::endl;
		mml::shell::normal();
		
		help();
		
		return 1;
	}
	
	else if (args.findArg("--help","-h")) {
		help();
		return 0;
	}
	
	else if ((args.findArg("-c","--calculate") /*|| args.findArg("-s","--summation")*/ || args.findArg("-m","--matrix")) && args.size() == 2) {
		mml::shell::warn("Fehlende Eingabe!");
	}
	
	else if (args.findArg("-c","--calculate")) {
		result = mml::rechner::calculate(args,args[args.positionArg("-c") + 1], true);
        mml::rechner::save_result(args, args[args.positionArg("-c","--calculate") + 1],result,calc_log);
    }
	
	else if (args.findArg("-cs","--calculations")) {
		std::vector<mml::string> equations;
		std::vector<double> results = mml::rechner::calculations(args, equations);
		
		// Save the results and equations
		for(uint32_t i = 0; i < equations.size(); i++)
			mml::rechner::save_result(args, equations[i], results[i],calc_log);
	}
	else if(args.findArg("-m","--matrix")) {

		/**
		 * NOTE Transform from latex matric to compatible format
		 * TODO
		 */
		
		if(args.findArg("-ml","--matrix-latex")) {
			mml::string temp = args[args.positionArg("-m","--matrix") + 1]; // Line with the matrix calculations
			mml::string temp_s = ""; // string to build the new calculations line
			bool braket = false;	// to indicate whether the matrix is finished or starts
			// Build string in compatible format:
			for(uint32_t i = 0; i < temp.size();i++) {
				if(temp[i] == '&')
					temp_s += ",";
				else if(temp[i] == '\\')
					temp_s += "],[";
				else if(temp[i] == '|' and braket){
					temp_s += "]]";
					braket = false;
				}
				else if(temp[i] == '|' and not braket) {
					temp_s += "[[";
					braket = true;
				}
				else
					temp_s = temp_s.str() + (char) temp[i];
			}
			args[args.positionArg("-m","--matrix") + 1] = temp_s;
		}

		args[args.positionArg("-m","--matrix") + 1] = args[args.positionArg("-m","--matrix") + 1].replace(" ",""); // Leerzeichen ersetzen, aber Achtung Matrix falsch wenn nicht mit " "
		
		if (args.findArg("-a","--adjugate")) {
			
			mml::math::matrix mat(args[args.positionArg("-m","--matrix") + 1].str());
			if(args.exist("-v","--verbose")) {
				std::cout << "The adjugate of the matrix" << std::endl;
				mat.print();
				std::cout << "is" << std::endl;
			}
			else
				std::cout << "The adjugate is" << std::endl;
			
			mat = mat.adjugate();
			mat.print();
			return 0;

		}
		else if (args.exist("-d","--det")) {
			mml::math::matrix mat(args[args.positionArg("-m","--matrix") + 1].str());
			if(args.exist("-v","--verbose")) {
				std::cout << "The determinant of the matrix" << std::endl;
				mat.print();
				std::cout << "is " << mat.det()<< "." << std::endl;
			}
			else
				std::cout << "The determinant is " << mat.det() << "." << std::endl;
			// TODO save matrix
		}
		else if (args.findArg("-i","--inverse")) {
			
			mml::math::matrix mat(args[args.positionArg("-m","--matrix") + 1].str());
			if(args.exist("-v","--verbose")) {
				std::cout << "The inverse of the matrix" << std::endl;
				mat.print();
				std::cout << "is" << std::endl;
			}
			else
				std::cout << "The inverse matrix is" << std::endl;
			
			mat = mat.inverse();
			mat.print();
			// TODO save matrix

		}
		else if (args.findArg("-tr","--transpose")) {
			
			mml::math::matrix mat(args[args.positionArg("-m","--matrix") + 1].str());
			if(args.exist("-v","--verbose")) {
				std::cout << "The transpose of the matrix" << std::endl;
				mat.print();
				std::cout << "is" << std::endl;
			}
			else
				std::cout << "The transposed matrix is" << std::endl;
			
			mat = mat.transpose();
			mat.print();
			// TODO save matrix
		}
		else {
			matrix = mml::rechner::matrix_calculation(args, args[args.positionArg("-m","--matrix") + 1]);
			mml::rechner::save_matrix(args, args[args.positionArg("-m","--matrix") + 1], matrix,calc_log);
		}
	}
	else if (args.findArg("-s","--summation")){
		mml::vector<double> values = mml::rechner::add(args);
		result = values.sum();
		values.log(calc_log, false, "[summation] ", " = " + std::to_string(result));
	}
	else if (args.findArg("-l","--log","-lv")) {
		if(mml::Unix::exist(calc_log)) {
			
			mml::log log(calc_log);
			log.print(args.exist("-v","--verbose","-lv"));
		}
		else
			std::cout << "Es existiert keine Logdatei!" << std::endl;
		return 0;
		
	}
	else if(args.findArg("-lr", "log_reset")) {
		mml::rechner::reset_logfile(args,calc_log);
		return 0;
	}
	
	else if(args.findArg("-lb","--log-backup")) {
		mml::rechner::backup_logfile(args, calc_log);
		return 0;
	}
	else {
		result = mml::rechner::calculate(args,args[1]);
        mml::rechner::save_result(args, args[1],result,calc_log);
    }
	
	if ((args.findArg("-c","--calculate") || args.findArg("-s", "--summation") || args.exist("+", "-", "*", "/")) && !args.findArg("-cs", "--calculations") && args.notArg("-m","--matrix")) {
		if(args.findArg("-p","--digits")) {
			// TODO betaphase
			std::cout << "Result (eventually wrong decimal point numbers!): " << std::setprecision(args[args.positionArg("-p","--digits")+1].atoi()) << result << std::endl;
			
		}
		else
			std::cout << "Result: " << result << std::endl;
	}
	
	
	if(args.findArg("-t","--timer"))
		std::cout << "Calculation time: " << time.range() << std::endl;

	return 0;
	
}
