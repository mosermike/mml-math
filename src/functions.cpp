#include <iostream>
#include <fstream>
#include <math.h>
//#include <format>
#include <limits>
#include <mml.hpp>
#include "../include/mml-math/functions.hpp"
#include "../include/mml-math/basic_operations.hpp"



mml::string mml::rechner::operations(mml::shell::arg args, mml::string equation, mml::string command, uint16_t tabs) {
	bool	verbose = args.exist("-v","--verbose");
	double	temp	= 0.0;
	// Verbose, Say what command is checked.
	if(verbose) {
		for(uint16_t i = 0; i < tabs; i++)
			std::cout << "\t";
		std::cout << "[" << command << "] " << equation;
		if(equation.exist(command.str()))
			std::cout << " " << ": Command exists!";
		std::cout << std::endl;
	}
	
	// ==================
	// Conditions to work
	// ==================
	if (command == "^") {
		command = "^(";
		// NOTE When there is no bracket => Error message
		if(equation[equation.find('^')+1] != '(' && equation.exist("^"))
			mml::shell::error("[Operations] After ^ is not a closing bracket!");
	}
	
	// ==========
	// Operations
	// ==========
	for (uint32_t i = 0; i < equation.size(); i++) {
		if(equation.substr(i,command.size()) == command) {
			std::size_t pos_auf = i;
			std::size_t pos_auf_others = 0;
			for (uint32_t j = i+command.size(); j < equation.size(); j++) {
				
				if(equation[j] == '('){
					pos_auf_others++;
				}
				else if(equation[j] == ')') { 
					if(pos_auf_others == 0) {
						// BEGIN Calculate all the operators and replace
						if(command =="ln(")
							equation = equation.replace(equation.sub(pos_auf,j),mml::to_string(std::log(rechnung(args,equation.sub(pos_auf+command.size(),j-1),tabs+1).atof())),pos_auf);
						else if(command == "log(")
							equation = equation.replace(equation.sub(pos_auf,j),mml::to_string(std::log10(rechnung(args,equation.sub(pos_auf+command.size(),j-1),tabs+1).atof())),pos_auf);
						else if(command == "log2(")
							equation = equation.replace(equation.sub(pos_auf,j),mml::to_string(std::log2(rechnung(args,equation.sub(pos_auf+command.size(),j-1),tabs+1).atof())), pos_auf);
// 						else if(command == "l")
// 							equation.replace(equation.sub(pos_auf,j),mml::to_string(std::log(rechnung(args,equation.sub(pos_auf+command.size(),j-1)).atof())),true, pos_auf);
						else if(command == "sqrt(") {
							temp = rechnung(args,equation.sub(pos_auf+command.size(),j-1),tabs+1).atof();
							if(temp < 0)
								mml::shell::warn("[sqrt] Domain error");
							equation = equation.replace(equation.sub(pos_auf,j),mml::to_string(std::sqrt(temp)), pos_auf);
						}
						else if(command == "exp(")
							equation = equation.replace(equation.sub(pos_auf,j),mml::to_string(std::exp(rechnung(args,equation.sub(pos_auf+command.size(),j-1),tabs+1).atof())), pos_auf);
						else if(command == "sin(") {
							temp = mml::rechner::rad_or_grad(args,rechnung(args,equation.sub(pos_auf+command.size(),j-1),tabs++).atof());
							equation = equation.replace(equation.sub(pos_auf,j),mml::to_string(std::sin(temp)), pos_auf);
						}
						else if(command == "arcsin(") {
							temp = rechnung(args,equation.sub(pos_auf+command.size(),j-1),tabs+1).atof();
							if (temp > 1 || temp < -1) // arcsin nur von -1 bis 1 definiert
								mml::shell::warn("[arcsin] Domain error");
							equation = equation.replace(equation.sub(pos_auf,j),mml::to_string(mml::rechner::grad_or_rad(args,std::asin(temp))), pos_auf);
						}
						else if(command == "cos(") {
							temp = mml::rechner::rad_or_grad(args,rechnung(args,equation.sub(pos_auf+command.size(),j-1),tabs++).atof());
							equation = equation.replace(equation.sub(pos_auf,j),mml::to_string(std::cos(temp)),pos_auf);
						}
						else if(command == "arccos(") {
							temp = rechnung(args,equation.sub(pos_auf+command.size(),j-1),tabs++).atof();
							if (temp > 1 || temp < -1)
								mml::shell::warn("[arcsin] Domain error");
							equation = equation.replace(equation.sub(pos_auf,j),mml::to_string(mml::rechner::grad_or_rad(args,std::acos(temp))),pos_auf);
							
						}
						else if(command == "tan(") {
							temp = mml::rechner::rad_or_grad(args,rechnung(args,equation.sub(pos_auf+command.size(),j-1),tabs++).atof());
							equation = equation = equation.replace(equation.sub(pos_auf,j),mml::to_string(mml::rechner::grad_or_rad(args,std::tan(temp))),pos_auf);
						}
						else if(command == "arctan(") {
							temp = rechnung(args,equation.sub(pos_auf+command.size(),j-1),tabs++).atof();
							equation = equation.replace(equation.sub(pos_auf,j),mml::to_string(mml::rechner::grad_or_rad(args,std::atan(temp))),pos_auf);
						}
						else if(command == "^(") {
							
							if(equation.exist("^(")) {
								
								// NOTE Determine base
								double base = 0;
								std::size_t base_pos = 0;
								
								// BEGIN base with brakets
								if( equation[pos_auf-1] == ')') {
									std::size_t pos_zu = pos_auf-1;
									uint32_t pos_zu_others = 0;
									
									for (uint32_t n = pos_zu-1; n >= 0; n--) {
										
										if(equation[n] == ')')
											pos_zu_others++;
										else if(equation[n] == '(') {
											if (pos_zu_others == 0) {
												base = mml::rechner::calculate_intern(equation.sub(n+1,pos_zu-1),verbose);
												
												// BEGIN Correctur so that with the exponent being even the base is positive and not negative
												if(base < 0) {
													if(verbose)
														std::cout << "base negative" << std::endl;
													if(equation.sub(pos_auf+command.size(),j-1).atoi() % 2 == 0)
														base = base*(-1);
												}
												// END Correctur...
												equation = equation.replace(equation.sub(n,pos_zu),mml::to_string(base),n); // replace base
												return mml::rechner::rechnung(args,equation);
												break;
											}
											else
												pos_zu_others--;
										}
									}
								}
								// END base with brakets
															
								for(int32_t t = pos_auf; t >= 0; t--){
									if ( t == 0 ) {
										if(equation[0] == '(') {
											base = equation.sub(t+1,pos_auf-1).atof();
											base_pos = 1;
											break;
										}
										else if(equation[0] != '-') {
											base = equation.sub(t,pos_auf-1).atof();
											break;
										}
										else {
											base = equation.sub(t,pos_auf-1).atof();
											base_pos = t;
											break;
										}
									}
									if(((equation[t] == '+' && equation[t-1] != 'e') || (equation[t] == '-'  && equation[t-1] != 'e')  || equation[t] == '/' || equation[t] == '(' || equation[t] == '*')) {
										base = equation.sub(t+1,pos_auf-1).atof();
										base_pos = t+1;
										break;
									}
																
								}
								
								// NOTE If in the exponent is an equation
								if(equation.sub(pos_auf+command.size(),j-1).exist("+","-","/","*")) {
									equation = equation.replace(equation.sub(base_pos,j),mml::to_string(std::pow(base,mml::rechner::rechnung(args,equation.sub(pos_auf+command.size(),j-1)).atof())), base_pos);
								}
								else
									equation = equation.replace(equation.sub(base_pos,j),mml::to_string(std::pow(base,equation.sub(pos_auf+command.size(),j-1).atof())),base_pos);
								equation = mml::rechner::rechnung(args,equation);
 								}
						}
						else if(command == "(") {
							equation = equation.replace(equation.sub(pos_auf,j),rechnung(args,equation.sub(pos_auf+1,j-1)), pos_auf);
						}
						else
							mml::shell::error("[Operations] " + command.str() + " is not working or not implemented. Please contact programmer");
						
						// END Calculate all the operators and replace
						i = 0;
						break;
						
					}
					else
						pos_auf_others--;
						
				}
			}
			
			i = 0;
		}
	}
	
	return equation;
}


std::size_t mml::rechner::pos_bracket(mml::string equation, std::size_t temp, std::size_t temp_end) {
	
	int		a			= 0;	// Anzahl an Klammer zu
	int		b			= 1;	// Anzahl Klammer auf
	
	
	for(uint32_t i = temp; i < equation.size(); i++) {
		// Abbruchbedingung:
		if(a >= b && a > 0)
			break;
		
		// Zählen wie viele Klammer auf
		if(equation[i] == '(')
			b++;
		// Zählen wie viele Klammer zu
		else if(equation[i] == ')') {
			a++;
		}
			
	}
	// Position von richtigem ) bestimmen:
	for(uint32_t i = temp; i < equation.size(); i++) {
		if(equation[i] == ')')
			a--;
		if(a <= 0)
			return i;
	}
	
	return temp_end;
}

double mml::rechner::rad_or_grad(mml::shell::arg args, double grad) {return args.exist("--grad") ? (double) grad/180*M_PI : grad;}
double mml::rechner::grad_or_rad(mml::shell::arg args, double grad) {return args.exist("--grad") ? (double) grad*180/M_PI : grad;}

// double mml::rechner::rad_to_grad(double rad) {return (double) 180 * rad/M_PI;}

mml::string mml::rechner::rechnung(mml::shell::arg args, mml::string equation, uint16_t tabs) {
		
 		bool	verbose	= args.exist("-v","--verbose");
		
	/*  ==================
	 *  NOTE bracket check 
	 *  ================== */
		uint8_t bra_o = 0; // brackets open
		uint8_t bra_c = 0; // brackets closed
		for(uint16_t i = 0; i < equation.size(); i++) {
			if(equation[i] == '(')
				bra_o++;
			else if(equation[i] == ')')
				bra_c++;
		}
		
		if (bra_o != bra_c)
			mml::shell::warn("[rechnung] number of open and closed brackets don't match!");
	//	END bracket check
		equation = operations(args,equation,"ln(", tabs);
		equation = operations(args,equation,"log(", tabs);
		equation = operations(args,equation,"log2(", tabs);
		equation = operations(args,equation,"sqrt(", tabs);
		equation = operations(args,equation,"exp(", tabs);
		equation = operations(args,equation,"arcsin(", tabs);
		equation = operations(args,equation,"sin(", tabs);
		equation = operations(args,equation,"arccos(", tabs);
		equation = operations(args,equation,"cos(", tabs);
		equation = operations(args,equation,"arctan(", tabs);
		equation = operations(args,equation,"tan(", tabs);
		equation = operations(args,equation,"^", tabs);
		equation = operations(args,equation,"(", tabs);
		if(verbose)
			std::cout << "Operations done" << std::endl;
 		equation = mml::to_string(mml::rechner::calculate_intern(equation,verbose,false));
		
		return equation;
}

mml::string mml::rechner:: replace(mml::shell::arg args, mml::string equation) {
	/**
	 * @note , durch . ersetzen
	 */
	equation = equation.replace(",",".");
		
	/** 
	 * @note Variablen ersetzen
	 */
	
	if(args.findArg("-u")){
			
		mml::string					variable				= "";
		mml::string					variables				= args[args.positionArg("-u") + 1];
		mml::string					value	 				= "";
		mml::string					var						= "";
		std::size_t					temp					= variables.find("=");
		std::size_t					pos						= variables.find(":");
		
		do{
			// die aktuelle Variable finden (alles bis zum =) und String kürzen inklusive =
			var = variables.substr(0,temp);
			
			// falls : vorhanden ist => weitere Variablen vorhanden
			if(pos < std::string::npos) {
				// Value bestimmen vor :
				value = variables.substr(temp + 1, pos - temp - 1).str();
				
				equation = equation.replace(var,value);
			}
			// kein : vorhanden, nur noch eine Variable übrig
			else {
				equation = equation.replace(var, variables.substr(temp + 1));		// Variable durch den Wert ersetzen
				break;
			}
			// variables kürzen
			variables = variables.substr(pos + 1);
			
			// Neue Positionen von = und , bestimmen
			temp = variables.find("=");
			pos = variables.find(",");
			
		} while(temp < std::string::npos);
	}
	
	/** 
	 * @note Physikalische Werte ersetzen
	 */
		equation = equation.replace("P_c", "299792458");										// Lichtgeschwindigkeit
		equation = equation.replace("P_µ", "1.256637e-6");								// Magnetische Permeabilität
		equation = equation.replace("P_e", "1.602177e-19");								// Elementarladung
		equation = equation.replace("P_k", "1.380648e-23");								// Boltzmann-Konstanten
		equation = equation.replace("P_h", "6.626070e-34");								// Planksches Wirkungsquantum
		equation = equation.replace("P_m", "9.109384e-31");								// Elektronenmasse
		equation = equation.replace("P_G", "6.67e-11");									// Gravitationskonstante
		equation = equation.replace("P_u", "1.660539066e-27");							// Atomare Masseneinheit
		equation = equation.replace("P_NA", "6.02214076e+23");							// Avogadro Konstante
	
	/**
	 * @note Mathematische Sachen ersetzen
	 */
		std::string pi = "3.14159265358979323846"; //std::format("{}\n", M_PI);
		equation = equation.replace("P_Pi",pi.c_str());		// PI herausfiltern und durch Wert ersetzen
		equation = equation.replace("Pi",pi.c_str());		// PI herausfiltern und durch Wert ersetzen
		equation = equation.replace("pi",pi.c_str());	// Pi herausfiltern und durch Wert ersetzen
		equation = equation.replace("PI",pi.c_str());	// Pi herausfiltern und durch Wert ersetzen
	
	/**
	 * @note e ersetzen
	 */
		if(equation.exist("E") || equation.exist("exp")) {
			
			if(equation.exist("E"))
				equation = equation.replace("E",std::to_string(M_E).c_str());	// e herausfiltern und durch Wert ersetzen
			
			else {
			
				for(uint32_t i = 0; i < equation.size(); i++) {
				
					if(equation[i] == 'E' && equation[i + 1] != 'x') {
					
						equation = equation.substr(0, i) + std::to_string(M_E) + equation.substr(i + 1).str();
						
						i += std::to_string(M_E).size();
						
						if(!equation.exist("E"))
							break;
					}
					
				}
			}
		
		}
	
		
	
	/** 
	 * @note SI-Präfixe ersetzen
	 */
		
		while(equation.exist("p","n","µ","m") || equation.exist("k","M","G","T")) {
			int32_t praefix = 0;
		
			if(equation.exist("p") && ((int) equation[equation.find("p")-1] > 47 && (int) equation[equation.find("p")-1] < 58))
				praefix = -12;
			else if(equation.exist("n") && ((int) equation[equation.find("n")-1] > 47 && (int) equation[equation.find("n")-1] < 58))
				praefix = -9;
			else if(equation.exist("µ") && ((int) equation[equation.find("µ")-1] > 47 && (int) equation[equation.find("µ")-1] < 58))
				praefix = -6;
			else if(equation.exist("m") && ((int) equation[equation.find("m")-1] > 47 && (int) equation[equation.find("m")-1] < 58))
				praefix = -3;
			else if(equation.exist("k") && ((int) equation[equation.find("k")-1] > 47 && (int) equation[equation.find("k")-1] < 58))
				praefix = 3;
			else if(equation.exist("M") && ((int) equation[equation.find("M")-1] > 47 && (int) equation[equation.find("M")-1] < 58))
				praefix = 6;
			else if(equation.exist("G") && ((int) equation[equation.find("G")-1] > 47 && (int) equation[equation.find("G")-1] < 58))
				praefix = 9;
			else if(equation.exist("T") && ((int) equation[equation.find("T")-1] > 47 && (int) equation[equation.find("T")-1] < 58))
				praefix = 12;
			
			if(!mml::atob(praefix))
				break;
			
			switch(praefix) {
				case -12 : equation = equation.replace("p","*0.000000000001")				; break;
				case -9  : equation = equation.replace("n","*0.000000001")					; break;
				case -6  : equation = equation.replace((std::string) "µ","*" + std::to_string(pow(10,praefix)))	; break;
				case -3  : equation = equation.replace((std::string) "m","*" + std::to_string(pow(10,praefix)))	; break;
				case  3  : equation = equation.replace((std::string) "k","*" + std::to_string(pow(10,praefix)))	; break;
				case  6  : equation = equation.replace((std::string) "M","*" + std::to_string(pow(10,praefix)))	; break;
				case  9  : equation = equation.replace((std::string) "G","*" + std::to_string(pow(10,praefix)))	; break;
				case  12 : equation = equation = equation.replace((std::string) "T","*" + std::to_string(pow(10,praefix)))	; break;
				default  : break;
			}
			
		}

	equation = mml::rechner::rechnung(args,equation);
	return equation;
// 	/**
// 	 * @note Klammerbehandlung 
// 	 */
// 	// TODO Überarbeiten!!
// 		if(equation.exist("(") && (equation.find("(") == 0 || (((int) equation[equation.find("(")- 1] < 58) && (int) equation[equation.find("(")-1] != 97))) {
// 			std::cout << equation << std::endl;
// 			std::size_t		length	= 1;	// Länge des Befehls
// 			std::size_t		auf		= 0;
// 			std::size_t		zu		= 0;	// Position zu
// 			mml::string		innen	= "";	// Klammerinhalt
// 			mml::string		value	= "";	// Ergebnis innen
// 			
// 			do {
// 				auf = equation.find("(") + length;
// 				// Vor Klammer kein Operator:
// 				if((int) equation[auf - 2] > 47) {
// 					equation = equation.substr(0,auf - 1).str() + "*" + equation.substr(auf - 1).str();
// 					auf++;	// Neue Position auf
// 				}
// 				
// 				// richtige Klammer zu bestimmen:
// 				zu = pos_bracket(equation,auf, zu);
// 				
// 				innen = equation.substr(auf, zu - auf);
// 				
// 				// weitere komplette Klammern (z.B. (1+1)) im Klammerinhalt:
// 				while(innen.exist("(")) {
// 					
// 					std::size_t		auf1	= innen.find("(") + length;
// 					std::size_t		zu1	= pos_bracket(innen, auf1 ,auf1 + 1);
// 					mml::string		inn		= innen.substr(auf1, zu1 - auf1);
// 					mml::string		val		= mml::to_string(calculate(args,inn,true));
// 					
// 					innen.replace(innen.substr(auf1 - length, zu1 - auf1 + length + 1), val, true);
// 					
// 				} 
// 				
// 				value = calculate(args,innen,true);
// 
// 				equation.replace(equation.substr(auf - length, zu - auf + length + 1), value,true );
// 		
// 			} while(equation.exist("("));
// 		}
// 		
// 		
// 	/** 
// 	 * @note Wurzel ziehen
// 	 * TODO überarbeiten
// 	 */
// 		if(equation.exist("sqrt")) {
// 			
// 			std::string		command		= "sqrt";	// Befehl
// 			mml::string		innen		= "";		// Werte in der Klammer
// 			mml::string		value		= "";		// Zielwert in der inneren Klammer
// 			std::size_t		temp		= equation.find(command);	// Position des Befehls
// 			std::size_t		length		= command.size() + 1;		// Länge des Befehls zum dazuaddieren
// 			std::size_t		temp_end	= equation.find(")",temp + length);	// Klammer zu, wobei wichtig, erst nach Befehl nachschauen
// 			
// 			do {
// 				
// 				temp += length;	// ansonsten Fehler bei Endbedingung
// 				
// 				// innerer Wert bestimmen:
// 				innen = equation.substr(temp, temp_end - temp);
// 				
// 				// Innere Klammer berechnen:
// 				if(innen.exist("+","-","*","/") || innen.exist("^","(")) {
// 					if(innen.exist("(")) {
// 						
// 						temp_end = pos_bracket(equation,temp,temp_end);
// 						
// 						innen = equation.substr(temp, temp_end - temp);
// 					}
// 					
// 					value = calculate(args,innen,true);
// 				
// 					equation.replace("(" + innen.str() + ")","(" + value.str() + ")",true);
// 					
// 					temp		= equation.find(command) + length;
// 					temp_end	= equation.find(")", temp);
// 				}
// 				
// 				// Wurzel bilden und in der Gleichung ersetzen
// 				equation.replace(equation.substr(temp - length, temp_end - temp + length + 1),std::to_string(std::sqrt(equation.substr(temp, temp_end - temp).atof())),true);
// 				
// 				// Weitere vorhanden?
// 				temp		= equation.find(command,temp + 1);
// 				temp_end	= equation.find(")", temp_end + 1);
// 				
// 				
// 			} while ( temp  < std::string::npos);
// 		}
// 	
// 	/** 
// 	 * @note logarithmus naturalis berechnen
// 	 * TODO überarbeiten
// 	 */
// 		if(equation.exist("ln")) {
// 			
// 			std::string		command		= "ln";
// 			mml::string		innen		= "";
// 			mml::string		value		= "";
// 			std::size_t		temp		= equation.find(command);
// 			std::size_t		length		= command.size() + 1;
// 			std::size_t		temp_end	= equation.find(")",temp + length);
// 			do {
// 				
// 		
// 				temp += length;	// ansonsten Fehler bei Endbedingung
// 				
// 				// innerer Wert bestimmen:
// 				innen = equation.substr(temp, temp_end - temp);
// 				
// 				// Innere Klammer berechnen:
// 				if(innen.exist("+","-","*","/") || innen.exist("^","(")) {
// 					if(innen.exist("(")) {
// 						// Position der richtigen Klammer bestimmen:
// 						temp_end = pos_bracket(equation,temp, temp_end);
// 						
// 						// Neue Werte bilden:
// 						innen = equation.substr(temp, temp_end - temp);
// 						
// 					}
// 					
// 					value = calculate(args,innen,true);
// 					
// 					equation.replace("(" + innen.str() + ")","(" + value.str() + ")",true);
// 					
// 					temp		= equation.find(command) + length;
// 					temp_end	= equation.find(")", temp);
// 				}
// 				
// 				// Logarithmus naturalis bilden und in der Gleichung ersetzen
// 				equation = equation.replace(equation.substr(temp - length, temp_end - temp + length + 1),std::to_string(std::log(std::atof(equation.substr(temp,temp_end - temp).c_str()))));
// 		
// 				temp		= equation.find(command,temp + 1);
// 				temp_end	= equation.find(")", temp_end + 1);
// 		
// 				
// 			} while ( temp  < std::string::npos);
// 			
// 		}
// 		
// 	/** 
// 	 * @note 10 logarithmus berechnen
// 	 */
// 		if(equation.exist("log(")) {
// 			std::string		command		= "log(";
// 			mml::string		innen		= "";
// 			mml::string		value		= "";
// 			std::size_t		temp		= equation.find(command);
// 			std::size_t		length		= command.size();
// 			std::size_t		temp_end	= equation.find(")",temp + length);
// 			
// 			do {
// 		
// 				temp += length;	// ansonsten Fehler bei Endbedingung
// 				
// 				// innerer Wert bestimmen:
// 				innen = equation.substr(temp, temp_end - temp);
// 				
// 				// Innere Klammer berechnen:
// 				if(innen.exist("+","-","*","/") || innen.exist("^","(")) {
// 					if(innen.exist("(")) {
// 						// Position der richtigen Klammer bestimmen:
// 						temp_end = pos_bracket(equation,temp, temp_end);
// 						
// 						// Neue Werte bilden:
// 						innen = equation.substr(temp, temp_end - temp);
// 					}
// 				
// 					value = calculate(args,innen,true);
// 				
// 					equation.replace("(" + innen.str() + ")","(" + value.str() + ")",true);
// 					
// 					temp		= equation.find(command) + length;
// 					temp_end	= equation.find(")", temp);
// 				}
// 								
// 				// 10 Logarithmus bilden und in der Gleichung ersetzen
// 				equation = equation.replace(equation.substr(temp - length, temp_end - temp + length + 1),std::to_string(std::log10(std::atof(equation.substr(temp,temp_end - temp).c_str()))));
// 		
// 				temp		= equation.find(command,temp + 1);
// 				if(mml::range(temp))
// 					temp_end	= equation.find(")", temp + 1);
// 		
// 				value = "";
// 			} while ( temp  < std::string::npos);
// 		
// 		}
// 		
// 	/** 
// 	 * @note 2 logarithmus berechnen
// 	 */
// 		if(equation.exist("log2")) {
// 			std::string		command		= "log2";
// 			mml::string		innen		= "";
// 			mml::string		value		= "";
// 			std::size_t		temp		= equation.find(command);
// 			std::size_t		length		= command.size() + 1;
// 			std::size_t		temp_end	= equation.find(")",temp + length);
// 			do {
// 		
// 				temp += length;	// ansonsten Fehler bei Endbedingung
// 				
// 				// innerer Wert bestimmen:
// 				innen = equation.substr(temp, temp_end - temp);
// 				
// 				// Innere Klammer berechnen:
// 				if(innen.exist("+","-","*","/") || innen.exist("^","(")) {
// 					if(innen.exist("(")) {
// 						// Position der richtigen Klammer bestimmen:
// 						temp_end = pos_bracket(equation,temp, temp_end);
// 						
// 						// Neue Werte bilden:
// 						innen = equation.substr(temp, temp_end - temp);
// 					}
// 					
// 					value = calculate(args,innen,true);
// 				
// 					equation.replace("(" + innen.str() + ")","(" + value.str() + ")",true);
// 					
// 					temp		= equation.find(command) + length;
// 					temp_end	= equation.find(")", temp);
// 				}
// 				
// 				// 10 Logarithmus bilden und in der Gleichung ersetzen
// 				equation = equation.replace(equation.substr(temp - length, temp_end - temp + length + 1),std::to_string(std::log2(equation.substr(temp,temp_end - temp).atof())));
// 		
// 				temp		= equation.find(command,temp + 1);
// 				temp_end	= equation.find(")", temp_end + 1);
// 		
// 				
// 			} while ( temp  < std::string::npos);
// 			
// 		}
// 		
// 	/** 
// 	 * @note b logarithmus berechnen
// 	 */
// 		if(equation.exist("log")) {
// 			std::string		command		= "log";
// 			mml::string		innen		= "";
// 			mml::string		value		= "";
// 			std::size_t		temp		= equation.find(command);
// 			std::size_t		length		= command.size() + 2;
// 			std::size_t		temp_end	= equation.find(")",temp + length);
// 			double			base		= 0.0;
// 			do {
// 				
// 				base = equation.substr(temp + 3, equation.find("(") - temp - 3).atof();
// 				
// 				temp += length;	// ansonsten Fehler bei Endbedingung
// 				
// 				// innerer Wert bestimmen:
// 				innen = equation.substr(temp, temp_end - temp);
// 				
// 				// Innere Klammer berechnen:
// 				if(innen.exist("+","-","*","/") || innen.exist("^","(")) {
// 					if(innen.exist("(")) {
// 						// Position der richtigen Klammer bestimmen:
// 						temp_end = pos_bracket(equation,temp, temp_end);
// 						
// 						// Neue Werte bilden:
// 						innen = equation.substr(temp, temp_end - temp);
// 					}
// 					
// 					value = calculate(args,innen,true);
// 				
// 					equation.replace("(" + innen.str() + ")","(" + value.str() + ")",true);
// 					
// 					temp		= equation.find(command) + length;
// 					temp_end	= equation.find(")", temp);
// 				}
// 				
// 				// Logarithmus zur Basis b bilden und in der Gleichung ersetzen
// 				equation = equation.replace(equation.substr(temp - length, temp_end - temp + length + 1),std::to_string((std::log10(equation.substr(temp,temp_end - temp).atof())/std::log10(base))));
// 				
// 				temp		= equation.find(command,temp + 1);
// 				temp_end	= equation.find(")", temp_end + 1);
// 		
// 				
// 			} while ( temp  < std::string::npos);
// 			
// 		}
// 		
// 	/** 
// 	 * @note e^x mit exp(x) berechnen
// 	 */
// 		if(equation.exist("exp")) {
// 			std::string		command		= "exp";
// 			mml::string		innen		= "";
// 			mml::string		value		= "";
// 			std::size_t		temp		= equation.find(command);
// 			std::size_t		length		= command.size() + 1;
// 			std::size_t		temp_end	= equation.find(")",temp + length);
// 			
// 			do {
// 		
// 				temp += length;	// ansonsten Fehler bei Endbedingung
// 				
// 				// innerer Wert bestimmen:
// 				innen = equation.substr(temp, temp_end - temp);
// 				
// 				// Innere Klammer berechnen:
// 				if(innen.exist("+","-","*","/") || innen.exist("^","(")) {
// 					if(innen.exist("(")) {
// 						// Position der richtigen Klammer bestimmen:
// 						temp_end = pos_bracket(equation,temp, temp_end);
// 						
// 						// Neue Werte bilden:
// 						innen = equation.substr(temp, temp_end - temp);
// 					}
// 					
// 					value = calculate(args,innen,true);
// 				
// 					equation.replace("(" + innen.str() + ")","(" + value.str() + ")",true);
// 					
// 					temp		= equation.find(command) + length;
// 					temp_end	= equation.find(")", temp);
// 				}
// 				
// 				// e^x bilden und in der Gleichung ersetzen
// 				equation = equation.replace(equation.substr(temp - length, temp_end - temp + length + 1),std::to_string(std::exp(equation.substr(temp,temp_end - temp).atof())));
// 		
// 				temp		= equation.find(command,temp + 1);
// 				temp_end	= equation.find(")", temp_end + 1);
// 		
// 				
// 			} while ( temp  < std::string::npos);
// 			
// 		}
// 	
// 	/** 
// 	 * @note arcsinus von einem Wert berechnen
// 	 */
// 		if(equation.exist("arcsin")) {
// 			
// 			std::string		command		= "arcsin";
// 			mml::string		innen		= "";
// 			mml::string		value		= "";
// 			std::size_t		temp		= equation.find(command);
// 			std::size_t		length		= command.size() + 1;
// 			std::size_t		temp_end	= equation.find(")",temp + length);
// 			double			calc		= 0; 
// 			
// 			do {
// 		
// 				temp += length;	// ansonsten Fehler bei Endbedingung
// 				
// 				// innerer Wert bestimmen:
// 				innen = equation.substr(temp, temp_end - temp);
// 				
// 				// Innere Klammer berechnen:
// 				if(innen.exist("+","-","*","/") || innen.exist("^","(")) {
// 					if(innen.exist("(")) {
// 						// Position der richtigen Klammer bestimmen:
// 						temp_end = pos_bracket(equation,temp, temp_end);
// 						
// 						// Neue Werte bilden:
// 						innen = equation.substr(temp, temp_end - temp);
// 						
// 					}
// 					
// 					value = calculate(args,innen,true);
// 				
// 					equation.replace("(" + innen.str() + ")","(" + value.str() + ")",true);
// 					
// 					temp		= equation.find(command) + length;
// 					temp_end	= equation.find(")", temp);
// 				}
// 				
// 				// grad zu rad
// 				if(args.exist("--grad"))
// 					calc = rad_to_grad(std::asin(equation.substr(temp,temp_end - temp).atof()));
// 				else
// 					calc = std::asin(equation.substr(temp,temp_end - temp).atof());
// 				
// 				// sin bilden und in der Gleichung ersetzen
// 				equation = equation.replace(equation.substr(temp - length, temp_end - temp + length + 1),std::to_string(calc));
// 		
// 				temp		= equation.find(command,temp + 1);
// 				temp_end	= equation.find(")", temp_end + 1);
// 					
// 			} while ( temp  < std::string::npos);
// 			
// 		}
// 		
// 	/** 
// 	 * @note sinus von einem Wert berechnen
// 	 */
// 		if(equation.exist("sin")) {
// 			
// 			std::string		command		= "sin";
// 			mml::string		innen		= "";
// 			mml::string		value		= "";
// 			std::size_t		temp		= equation.find(command);
// 			std::size_t		length		= command.size() + 1;
// 			std::size_t		temp_end	= equation.find(")",temp + length);
// 			double			calc		= 0; 
// 			
// 			do {
// 		
// 				temp += length;	// ansonsten Fehler bei Endbedingung
// 				
// 				// innerer Wert bestimmen:
// 				innen = equation.substr(temp, temp_end - temp);
// 				
// 				// Innere Klammer berechnen:
// 				if(innen.exist("+","-","*","/") || innen.exist("^","(")) {
// 					if(innen.exist("(")) {
// 						// Position der richtigen Klammer bestimmen:
// 						temp_end = pos_bracket(equation,temp, temp_end);
// 						
// 						// Neue Werte bilden:
// 						innen = equation.substr(temp, temp_end - temp);
// 						
// 					}
// 					
// 					value = calculate(args,innen,true);
// 				
// 					equation.replace("(" + innen.str() + ")","(" + value.str() + ")",true);
// 					
// 					temp		= equation.find(command) + length;
// 					temp_end	= equation.find(")", temp);
// 				}
// 				
// 				// grad zu rad
// 				if(args.exist("--grad"))
// 					calc = grad_to_rad(equation.substr(temp,temp_end - temp).atof());
// 				else
// 					calc = equation.substr(temp,temp_end - temp).atof();
// 				
// 				// sin bilden und in der Gleichung ersetzen
// 				equation = equation.replace(equation.substr(temp - length, temp_end - temp + length + 1),std::to_string(std::sin(calc)));
// 		
// 				temp		= equation.find(command,temp + 1);
// 				temp_end	= equation.find(")", temp_end + 1);
// 					
// 			} while ( temp  < std::string::npos);
// 			
// 		}
// 	
// 	/** 
// 	 * @note arcsinus von einem Wert berechnen
// 	 */
// 		if(equation.exist("arccos")) {
// 			
// 			std::string		command		= "arccos";
// 			mml::string		innen		= "";
// 			mml::string		value		= "";
// 			std::size_t		temp		= equation.find(command);
// 			std::size_t		length		= command.size() + 1;
// 			std::size_t		temp_end	= equation.find(")",temp + length);
// 			double			calc		= 0; 
// 			
// 			do {
// 		
// 				temp += length;	// ansonsten Fehler bei Endbedingung
// 				
// 				// innerer Wert bestimmen:
// 				innen = equation.substr(temp, temp_end - temp);
// 				
// 				// Innere Klammer berechnen:
// 				if(innen.exist("+","-","*","/") || innen.exist("^","(")) {
// 					if(innen.exist("(")) {
// 						// Position der richtigen Klammer bestimmen:
// 						temp_end = pos_bracket(equation,temp, temp_end);
// 						
// 						// Neue Werte bilden:
// 						innen = equation.substr(temp, temp_end - temp);
// 						
// 					}
// 					
// 					value = calculate(args,innen,true);
// 				
// 					equation.replace("(" + innen.str() + ")","(" + value.str() + ")",true);
// 					
// 					temp		= equation.find(command) + length;
// 					temp_end	= equation.find(")", temp);
// 				}
// 				
// 				// grad zu rad
// 				if(args.exist("--grad"))
// 					calc = rad_to_grad(std::acos(equation.substr(temp,temp_end - temp).atof()));
// 				else
// 					calc = std::acos(equation.substr(temp,temp_end - temp).atof());
// 				
// 				// sin bilden und in der Gleichung ersetzen
// 				equation = equation.replace(equation.substr(temp - length, temp_end - temp + length + 1),std::to_string(calc));
// 		
// 				temp		= equation.find(command,temp + 1);
// 				temp_end	= equation.find(")", temp_end + 1);
// 					
// 			} while ( temp  < std::string::npos);
// 			
// 		}
// 		
// 	/** 
// 	 * @note cosinus von einem Wert berechnen
// 	 */
// 		if(equation.exist("cos")) {
// 			
// 			std::string		command		= "cos";
// 			mml::string		innen		= "";
// 			mml::string		value		= "";
// 			std::size_t		temp		= equation.find(command);
// 			std::size_t		length		= command.size() + 1;
// 			std::size_t		temp_end	= equation.find(")",temp + length);
// 			double			calc		= 0;
// 			do {
// 		
// 				temp += length;	// ansonsten Fehler bei Endbedingung
// 				
// 				// innerer Wert bestimmen:
// 				innen = equation.substr(temp, temp_end - temp);
// 				
// 				// Innere Klammer berechnen:
// 				if(innen.exist("+","-","*","/") || innen.exist("^","(")) {
// 					if(innen.exist("(")) {
// 						// Position der richtigen Klammer bestimmen:
// 						temp_end = pos_bracket(equation,temp, temp_end);
// 						
// 						// Neue Werte bilden:
// 						innen = equation.substr(temp, temp_end - temp);
// 						
// 					}
// 					
// 					value = calculate(args,innen,true);
// 				
// 					equation.replace("(" + innen.str() + ")","(" + value.str() + ")",true);
// 					
// 					temp		= equation.find(command) + length;
// 					temp_end	= equation.find(")", temp);
// 				}
// 				
// 				if(args.exist("--grad"))
// 					calc = grad_to_rad(equation.substr(temp,temp_end - temp).atof());
// 				else
// 					calc = equation.substr(temp,temp_end - temp).atof();
// 					
// 				// Logarithmus naturalis bilden und in der Gleichung ersetzen
// 				equation = equation.replace(equation.substr(temp - length, temp_end - temp + length + 1),std::to_string(std::cos(calc)));
// 		
// 				temp		= equation.find(command,temp + 1);
// 				temp_end	= equation.find(")", temp_end + 1);
// 		
// 				
// 			} while ( temp  < std::string::npos);
// 			
// 		}
// 	
// 	/** 
// 	 * @note arcsinus von einem Wert berechnen
// 	 */
// 		if(equation.exist("arctan")) {
// 			
// 			std::string		command		= "arctan";
// 			mml::string		innen		= "";
// 			mml::string		value		= "";
// 			std::size_t		temp		= equation.find(command);
// 			std::size_t		length		= command.size() + 1;
// 			std::size_t		temp_end	= equation.find(")",temp + length);
// 			double			calc		= 0; 
// 			
// 			do {
// 		
// 				temp += length;	// ansonsten Fehler bei Endbedingung
// 				
// 				// innerer Wert bestimmen:
// 				innen = equation.substr(temp, temp_end - temp);
// 				
// 				// Innere Klammer berechnen:
// 				if(innen.exist("+","-","*","/") || innen.exist("^","(")) {
// 					if(innen.exist("(")) {
// 						// Position der richtigen Klammer bestimmen:
// 						temp_end = pos_bracket(equation,temp, temp_end);
// 						
// 						// Neue Werte bilden:
// 						innen = equation.substr(temp, temp_end - temp);
// 						
// 					}
// 					
// 					value = calculate(args,innen,true);
// 				
// 					equation.replace("(" + innen.str() + ")","(" + value.str() + ")",true);
// 					
// 					temp		= equation.find(command) + length;
// 					temp_end	= equation.find(")", temp);
// 				}
// 				
// 				// grad zu rad
// 				if(args.exist("--grad"))
// 					calc = rad_to_grad(std::atan(equation.substr(temp,temp_end - temp).atof()));
// 				else
// 					calc = std::atan(equation.substr(temp,temp_end - temp).atof());
// 				
// 				// sin bilden und in der Gleichung ersetzen
// 				equation = equation.replace(equation.substr(temp - length, temp_end - temp + length + 1),std::to_string(calc));
// 		
// 				temp		= equation.find(command,temp + 1);
// 				temp_end	= equation.find(")", temp_end + 1);
// 					
// 			} while ( temp  < std::string::npos);
// 			
// 		}
// 	/** 
// 	 * @note tangens von einem Wert berechnen
// 	 */
// 		if(equation.exist("tan")) {
// 			
// 			std::string		command		= "tan";
// 			mml::string		innen		= "";
// 			mml::string		value		= "";
// 			std::size_t		temp		= equation.find(command);
// 			std::size_t		length		= command.size() + 1;
// 			std::size_t		temp_end	= equation.find(")",temp + length);
// 			double			calc		= 0;
// 			do {
// 
// 				temp += length;	// ansonsten Fehler bei Endbedingung
// 				
// 								// innerer Wert bestimmen:
// 				innen = equation.substr(temp, temp_end - temp);
// 				
// 				/// Innere Klammer berechnen:
// 				if(innen.exist("+","-","*","/") || innen.exist("^","(")) {
// 					if(innen.exist("(")) {
// 						// Position der richtigen Klammer bestimmen:
// 						temp_end = pos_bracket(equation,temp, temp_end);
// 						
// 						// Neue Werte bilden:
// 						innen = equation.substr(temp, temp_end - temp);
// 						
// 					}
// 					
// 					value = calculate(args,innen,true);
// 				
// 					equation.replace("(" + innen.str() + ")","(" + value.str() + ")",true);
// 					
// 					temp		= equation.find(command) + length;
// 					temp_end	= equation.find(")", temp);
// 				}
// 				
// 				if(args.exist("--grad"))
// 					calc = grad_to_rad(equation.substr(temp,temp_end - temp).atof());
// 				else
// 					calc = equation.substr(temp,temp_end - temp).atof();
// 					
// 				// tangens berechnen und in der Gleichung ersetzen
// 				equation = equation.replace(equation.substr(temp - length, temp_end - temp + length + 1),std::to_string(std::tan(calc)));
// 		
// 				temp		= equation.find(command,temp + 1);
// 				temp_end	= equation.find(")", temp_end + 1);
// 				
// 				
// 			} while ( temp  < std::string::npos);
// 			
// 		}
// 		
// 
// 		
// 	/**
// 	 * @note Potenzwert berechnen mit Klammern
// 	 * 
// 	 */
// 
// 		if(equation.exist("^(")) {
// 			
// 			std::string		command		= "^(";
// 			mml::string		innen		= "";
// 			mml::string		value		= "";
// 			mml::string		basis		= "";
// 			std::size_t		temp		= equation.find(command);
// 			std::size_t		length		= command.size();
// 			std::size_t		temp_end	= equation.find(")",temp + length);
// 			std::size_t		factor_pos	= 0;
// 			
// 			do {
// 				
// 				temp += length;	// ansonsten Fehler bei Endbedingung
// 				
// 				// innerer Wert bestimmen:
// 				innen = equation.substr(temp, temp_end - temp);
// 
// 				// Innere Klammer berechnen:
// 				if(innen.exist("+","-","*","/") || innen.exist("^","(")) {
// 					
// 					if(innen.exist("(")) {
// 						// Position der richtigen Klammer bestimmen:
// 						temp_end = pos_bracket(equation,temp, temp_end);
// 						
// 						// Neue Werte bilden:
// 						innen = equation.substr(temp, temp_end - temp);
// 						
// 					}
// 					
// 					value = calculate(args,innen,true);
// 					
// 					equation.replace("(" + innen.str() + ")","(" + value.str() + ")",true);
// 					
// 					temp		= equation.find(command) + length;
// 					temp_end	= equation.find(")", temp);
// 					innen = equation.substr(temp, temp_end - temp);
// 				}
// 				
// 				// Basis bestimmen:
// 				if(!equation.substr(0,temp).exist("+","*","/","-"))	// Keine Operator vor der Basis:
// 					basis = equation.substr(0, temp - length );
// 				else {
// 					for(uint32_t i = temp - length - 1; i >= 0; i--) {
// 						if((int) equation[i] < 46 || equation[i] == '/' || (int) equation[i] > 64) {
// 							basis = equation.substr(i + 1, temp - length - i - 1);
// 							factor_pos = i + 1; // Position vor Basis bestimmen
// 							break;
// 						}
// 					}
// 				}
// 				
// 				// Potenz berechnen und in der Gleichung ersetzen
// 				equation = equation.replace(equation.substr(factor_pos, temp_end - factor_pos + 1),std::to_string(std::pow(basis.atof(),innen.atof())));
// 				
// 				temp		= equation.find(command,temp + 1);
// 				temp_end	= equation.find(")", temp_end + 1);
// 				
// 				
// 			} while ( temp  < std::string::npos);
// 			
// 		}
// 	
// 	/**
// 	 * @note Potenzwert berechnen und ersetzen ohne Klammer
// 	 */
// 	
// 		if(mml::range(equation.find("^"))) {
// 			
// 
// 			std::size_t		temp			= equation.find("^");
// 			std::size_t		temp1			= 0;	// Wert vor Basis
// 			std::size_t		temp2			= 0;	// Wert nach Exponent
// 			
// 			do {
// 			
// 			mml::string		base			= "";
// 			double			exponent		= std::atof(equation.substr(temp + 1).c_str());
// 			
// 			// Position vor Basis identifizieren:
// 			for(uint32_t i = temp - 1; i > 0; i--) {
// 				temp1 = (int) equation[i] < 46 ? i : 0;
// 				if(temp1 == 0)
// 					temp1 = (int) equation[i] == 47? i : 0;
// 			
// 				if(temp1 > 0)
// 					break;
// 			}
// 			
// 			// Position nach Exponent identifizieren:
// 			for(uint32_t i = temp + 2; i < equation.size(); i++) {
// 				temp2 = (int) equation[i] < 46? i : 0;
// 				if(temp2 == 0)
// 					temp2 = (int) equation[i] == 47? i : 0;
// 				if(temp2 > 0)
// 					break;
// 			}
// 			
// 			// Korrektur, wenn vor der Basis ein Wert, ansonsten hat er einen Fehler wenn keiner da ist
// 			if(temp1 > 0)
// 				temp1++;
// 			// Ansonsten overvflow
// 			if(temp2 == 0)
// 				temp2 = equation.size();
// 			
// 			
// 			base = equation.substr(temp1, temp - temp1);
// 			
// 			// Wert bilden und ersetzen
// 			equation.replace(equation.substr(temp1,temp2 - temp1),std::to_string(pow(base.atof(),exponent)),true);
// 			
// 			temp			= equation.find("^", temp + 1);
// 			temp1			= 0;	// Wert vor Basis
// 			temp2			= 0;	// Wert nach Exponent
// 			
// 			} while (temp < std::string::npos);
// 			
// 		}
// 		
// 	
// 	
// 	return equation;
}


