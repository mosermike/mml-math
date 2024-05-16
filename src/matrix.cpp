#include <mml.hpp>
#include "../include/mml-math/matrix.hpp"
#include "../include/mml-math/logging.hpp"


mml::string mml::rechner::matrix_calculation(mml::shell::arg args, mml::string matrix) {
	
	std::size_t		pos		= 0;
	std::size_t		pos1 = 0;
	std::size_t		pos2 = 0;
	mml::string 	matrix1 = "";
	mml::string 	matrix2 = "";
	mml::string		temp = "";
	mml::string		matrix_l1 = matrix;
		
	// =========================
	// Matrizenmultiplikationen:
	// =========================
	if(matrix.exist("*")) {
		do {
			// Zwei Matrizen finden
			pos = matrix.find("*");
			
			// Erste Matrix finden
			pos1 = 0;
			for(uint32_t i = pos-1; i > 0; i--) {
				if (matrix[i+1] == '[') {
					if(matrix[i] == '+' || matrix [i] == '-' || matrix [i] == '*') {
						pos1 = i+1;
						break;
					}
				}
			}
			matrix1 = matrix.sub(pos1,pos-1);
			
			// zweite Matrix finden
			pos2 = matrix.size() - 1;
			for(uint32_t i = pos + 1; i < matrix.size(); i++) {
				if (matrix[i-1] == ']') {
					if(matrix[i] == '+' || matrix [i] == '-' || matrix [i] == '*') {
						pos2 = i-1;
						break;
					}
				}
			}
			matrix2 = matrix.sub(pos+1,pos2);
			temp = matrix_multiply(matrix1, matrix2);
			matrix.replace((mml::string) (matrix1.str() + "*" + matrix2.str()), mml::to_string(("[" + temp.str() + "]").c_str()), true);

			
		} while(matrix.exist("*"));
	}

	// =================
	// Matrizenaddition:
	// =================
	if(mml::range(matrix.find("+"))) {
		do {
			// Zwei Matrizen finden
			pos = matrix.find("+");
			
			// Erste Matrix finden
			pos1 = 0;
			for(uint32_t i = pos-1; i > 0; i--) {
				if (matrix[i+1] == '[') {
					if(matrix[i] == '+' || matrix [i] == '-' || matrix [i] == '*') {
						pos1 = i+1;
						break;
					}
				}
			}
			matrix1 = matrix.sub(pos1,pos-1);
			
			// zweite Matrix finden
			pos2 = matrix.size() - 1;
			for(uint32_t i = pos + 1; i < matrix.size(); i++) {
				if (matrix[i-1] == ']') {
					if(matrix[i] == '+' || matrix [i] == '-' || matrix [i] == '*') {
						pos2 = i-1;
						break;
					}
				}
			}
			matrix2 = matrix.sub(pos+1,pos2);
			temp = matrix_addition(matrix1, matrix2);
			matrix.replace((mml::string) (matrix1.str() + "+" + matrix2.str()), mml::to_string(("[" + temp.str() + "]").c_str()), true);

			
		} while(matrix.exist("+"));
	}
	
	// ====================
	// Matrizensubtraktion:
	// ====================
	if(matrix.exist("-[")) {
		do {
			// Zwei Matrizen finden
			pos = matrix.find("-");
			
			// Erste Matrix finden
			pos1 = 0;
			for(uint32_t i = pos-1; i > 0; i--) {
				if (matrix[i+1] == '[') {
					if(matrix[i] == '+' || matrix [i] == '-' || matrix [i] == '*') {
						pos1 = i+1;
						break;
					}
				}
			}
			matrix1 = matrix.sub(pos1,pos-1);
			
			// zweite Matrix finden
			pos2 = matrix.size() - 1;
			for(uint32_t i = pos + 1; i < matrix.size(); i++) {
				if (matrix[i-1] == ']') {
					if(matrix[i] == '+' || matrix [i] == '-' || matrix [i] == '*') {
						pos2 = i-1;
						break;
					}
				}
			}
			matrix2 = matrix.sub(pos+1,pos2);
			temp = matrix_addition(matrix1, matrix2,'-');
			matrix.replace((mml::string) (matrix1.str() + "-" + matrix2.str()), mml::to_string(("[" + temp.str() + "]").c_str()), true);

			
		} while(matrix.exist("-"));
	}
	// TEMP
	//std::cout << "Matrix in Eingabeform(temporär): " << matrix << std::endl;
	// TEMP
	
	mml::rechner::matrix_print(matrix);
	return matrix;
}


mml::string mml::rechner::matrix_addition(mml::string matrix1, mml::string matrix2, char op, bool ausgabe) {
	
	std::size_t		rows1		= 0; // Zeile Matrix 1
	std::size_t		rows2		= 0; // Zeile Matrix 2
	std::size_t		columns1	= 1; // Spalte Matrix 1
	std::size_t		columns2	= 1; // Spalte Matrix 2
	std::size_t		temp1		= 0;
	std::size_t		temp2		= 0;
	mml::string		temp		= "";
	mml::string		ergebnis	= "";
	
	// =================================================
	// Korrektur, wenn Matrix nicht mit [[ oder ]] endet
	// =================================================
	if(matrix1[1] != '[')
		matrix1 = "[" + matrix1.str();
	if(matrix1[matrix1.size()-2] != ']')
		matrix1 = matrix1.str() + "]";

	if(matrix2[1] != '[')
		matrix2 = "[" + matrix2.str();
	if(matrix2[matrix2.size()-2] != ']')
		matrix2 = matrix2.str() + "]";

	// =============================
	// Größe der Matrix 1 bestimmen:
	// =============================
	// Anzahl Zeilen
	for(uint32_t i = 1; i < matrix1.size(); i++) {
		if(matrix1[i] == '[')
				rows1++;
		
	}
	// Anzahl Spalten	
	temp1 = 1;
	temp2 = matrix1.find(']');
	temp = matrix1.sub(temp1,temp2);
	
	for(uint32_t i = 0; i < temp.size(); i++)
		if(temp[i] == ',')
			columns1++;
		
	// =============================
	// Größe der Matrix 2 bestimmen:
	// =============================
	// Anzahl Zeilen
	for(uint32_t i = 1; i < matrix2.size(); i++) {
		if(matrix2[i] == '[')
				rows2++;
		
	}
	// Anzahl Spalten	
	temp1 = 1;
	temp2 = matrix2.find(']');
	temp = matrix2.sub(temp1,temp2);
	
	for(uint32_t i = 0; i < temp.size(); i++)
		if(temp[i] == ',')
			columns2++;
	// ===============================
	// Überprüfen, ob Addition möglich
	// ===============================
	if(rows1 != rows2)
		mml::shell::warn("| Anzahl der Zeilen unterschiedlich!");
	if(columns1 != columns2)
		mml::shell::warn("| Anzahl der Spalten unterschiedlich!");	
	
	// ===================================
	//Umwandlung des Strings in ein Array:
	// ===================================
	double mat1[rows1][columns1];
	double mat2[rows2][columns2];
	double mat3[rows1][columns1];
	
	// Erste Klammern löschen:
	matrix1 = matrix1.substr(1);
	matrix2 = matrix2.substr(1);
	
	// Werte zuweisen Matrix1
	for(uint32_t i = 0; i < rows1; i++) {
		temp1	= matrix1.find('[');
		temp2	= matrix1.find(']');
		temp	= matrix1.sub(temp1+1,temp2-1);
		matrix1 = matrix1.substr(temp2+2);
		
		for(uint32_t j = 0; j < columns1; j++) {
			if(temp.exist(",")) {
				mat1[i][j] = mml::atof((temp.sub(0,temp.find(',')-1)).str());
				temp = temp.substr(temp.find(',')+1);
			}
			else {
		
				mat1[i][j] = temp.atof();
		
			} 
		}
	}

	// Werte zuweisen Matrix2
	for(uint32_t i = 0; i < rows2; i++) {
		temp1	= matrix2.find('[');
		temp2	= matrix2.find(']');
		temp	= matrix2.sub(temp1+1,temp2-1);
		matrix2 = matrix2.substr(temp2+2);
		
		for(uint32_t j = 0; j < columns2; j++) {
			if(temp.exist(",")) {
				mat2[i][j] = mml::atof((temp.sub(0,temp.find(',')-1)).str());
				temp = temp.substr(temp.find(',')+1);
			}
			else {
				mat2[i][j] = temp.atof();
				break;
			}
			
		}
	}
	
	// ============================
	// Matrixaddition/-subtraktion:
	// ============================
	for(uint32_t i = 0; i < rows2; i++) {
		for(uint32_t j = 0; j < columns2; j++)  {
			if(op == '+')
				mat3[i][j] = mat1[i][j] + mat2[i][j];
			else if(op == '-')
				mat3[i][j] = mat1[i][j] - mat2[i][j];
		}
	}
	 // TODO komplette Rechnung ausgeben

	
	// =============================
	// Ergebnis in String umwandeln:
	// =============================
	for(uint32_t i = 0; i < rows1; i++) {
		ergebnis += "[";
		for(uint32_t j = 0; j < columns2; j++) {
			// Korrektur von std::to_string, da dies min. 8 Nachkommastellen anhängt
			temp = mat3[i][j];
			while(temp[temp.size()-1] == '0')
				temp = temp.sub(0,temp.size()-2);
	
			// Korrektur, wenn eine ganze Zahl vorhanden
			if(temp[temp.size()-1]== '.')
				temp = temp.sub(0,temp.size()-2);
			
			ergebnis += temp;
			if(j < columns2-1)
				ergebnis += ",";
			
		}
		ergebnis += "],";
	}
	ergebnis = ergebnis.substr(0,ergebnis.size()-2) + "]";
	
	// ==================
	// Ergebnis ausgeben:
	// ==================
	if(ausgabe) {
		matrix_print(ergebnis);
	}
	
	return ergebnis;
	
	
}


mml::string mml::rechner::matrix_adjunct(mml::string matrix, bool ausgabe) {
	std::size_t rows = 0; // Zeile Matrix
	std::size_t columns = 1; // Spalte Matrix
	std::size_t temp1 = 0;
	std::size_t temp2 = 0;
	mml::string temp = "";
	mml::string		ergebnis = "";
	
	// Fehlerkorrektur, falls Anfangs und Endklammern fehlen
	if(matrix[1] != '[')
		matrix = "[" + matrix.str() + "]";
	
	// =============================
	// Größe der Matrix bestimmen:
	// =============================
	// Anzahl Zeilen
	for(uint32_t i = 1; i < matrix.size(); i++) {
		if(matrix[i] == '[')
				rows++;
		
	}
	
	// Anzahl Spalten	
	temp1 = 1;
	temp2 = matrix.find(']');
	temp = matrix.sub(temp1,temp2);
	
	for(uint32_t i = 0; i < temp.size(); i++)
		if(temp[i] == ',')
			columns++;
	
	// ===================================
	//Umwandlung des Strings in ein Array:
	// ===================================
	//double mat[rows][columns];
	double adj[columns][rows];
	
	// ===================
	// Adjunkte berechnen:
	// ===================
	for(uint32_t i = 0; i < rows; i++) {
		for(uint32_t j = 0; j < columns; j++) {
			adj[i][j] = (std::pow(-1,i+j+2)) * (matrix_determinante(matrix_smaller(matrix,i,j,false),false));
		}
	}
	
	// =============================
	// Ergebnis in String umwandeln:
	// =============================
	for(uint32_t i = 0; i < columns; i++) {
		ergebnis += "[";
		for(uint32_t j = 0; j < rows; j++) {
				// Korrektur von std::to_string, da dies min. 8 Nachkommastellen anhängt
			temp = adj[i][j];
			while(temp[temp.size()-1] == '0')
				temp = temp.sub(0,temp.size()-2);
	
			// Korrektur, wenn eine ganze Zahl vorhanden
			if(temp[temp.size()-1]== '.')
				temp = temp.sub(0,temp.size()-2);
			
			ergebnis += temp;
			if(j < rows-1)
				ergebnis += ",";
			
		}
		ergebnis += "],";
	}
	ergebnis = ergebnis.substr(0,ergebnis.size()-2) + "]";
	
	// Fehlerkorrektur, falls Anfangs und Endklammern fehlen
	if(ergebnis[1] != '[')
		ergebnis = "[" + ergebnis.str() + "]";
	
	// Matrix Transponieren
	ergebnis = matrix_transposed(ergebnis, false);
	
	if(ausgabe) {
		std::cout << "Die Adjunkte der Matrix ist: " << std::endl;
		matrix_print(ergebnis);
	}

	return ergebnis;
}


double mml::rechner::matrix_determinante(mml::string matrix, const bool ausgabe) {
	double determinante = 1;
	std::size_t rows = 0; // Zeile Matrix
	std::size_t columns = 1; // Spalte Matrix
	std::size_t temp1 = 0;
	std::size_t temp2 = 0;
	mml::string temp = "";
	std::string	ergebnis = "";

	// =============================
	// Größe der Matrix bestimmen:
	// =============================
	// Anzahl Zeilen
	for(uint32_t i = 1; i < matrix.size(); i++) {
		if(matrix[i] == '[')
				rows++;
		
	}
	
	// Anzahl Spalten	
	temp1 = 1;
	temp2 = matrix.find(']');
	temp = matrix.sub(temp1,temp2);
	
	for(uint32_t i = 0; i < temp.size(); i++)
		if(temp[i] == ',')
			columns++;


	// ===============================
	// Überprüfen, ob Multiplikation möglich
	// ===============================
	if(columns != rows)
		mml::shell::warn("| Determinante nicht definiert!");	
	
	// ===================================
	//Umwandlung des Strings in ein Array:
	// ===================================
	double erg[rows][columns];
	
	// Erste Klammern löschen:
	matrix = matrix.substr(1);
	
	// Werte zuweisen Matrix
	for(uint32_t i = 0; i < rows; i++) {
		temp1	= matrix.find('[');
		temp2	= matrix.find(']');
		temp	= matrix.sub(temp1+1,temp2-1).str();
		matrix = matrix.substr(temp2+2);
		
		for(uint32_t j = 0; j < columns; j++) {
			if(temp.exist(",")) {
				erg[i][j] = mml::atof((temp.sub(0,temp.find(',')-1)).str());
				temp = temp.substr(temp.find(',')+1);
			}
			else {
				erg[i][j] = temp.atof();
			} 
		}
	}
	
	// Check if one column or row is 0
	for (uint16_t i = 0; i < rows; i++) {
		bool zero_line = true;
		for (uint16_t j = 0; j < columns; j++) {
			if(erg[i][j] > 1e-8  || erg[i][j] < -1e-8) {
				zero_line = false;
				break;
			}
		}
		if (zero_line) {
			if(ausgabe == 1)
				std::cout << "Die Determinante der Matrix ist: 0.0"<< std::endl;
			return 0.0;
		}
	}
	
	for (uint16_t j = 0; j < columns; j++) {
		bool zero_line = true;
		for (uint16_t i = 0; i < rows; i++) {
			if(erg[i][j] > 1e-8 || erg[i][j] < -1e-8) {
				zero_line = false;
				break;
			}
		}
		if (zero_line) {
			if(ausgabe == 1)
				std::cout << "Die Determinante der Matrix ist: 0.0"<< std::endl;
			return 0.0;
		}
	}
	
	// =================
	// Gauß-Algorithmus:
	// =================
	// Alle Zeilen durchgehen und dabei Einträge von [n][n] ignorieren, da alle =0
	for(uint32_t n = 0; n < rows; n++) {
		// Eine Zeilenberechnung:
		for(uint32_t i = n; i < rows-1; i++) {

			// Vertauschen von zwei Zeilen, damit nicht durch 0 geteilt wird
			if(erg[n][n] == 0.0) {
				int m = n+1;
				determinante = determinante * (-1);
				do {
					// start from the start if m bigger than rows
					if (m >= (int) rows)
						m = 0;

					// Vertauschen durchführen, falls Bedingung stimmt:
					if(abs(erg[m][n]) > 1e-50) {
						for(uint32_t m1 = 0; m1 < columns; m1++) {
							std::swap(erg[n][m1],erg[m][m1]);
						}
					}
					else
						m++;
				} while(abs(erg[n][n]) < 1e-50);
			}
			
			// Kleiner als ein Schwellwert: Zahl eigentlich 0
			if(erg[n][n] < 1e-100 && erg[n][n] > -1e-100)  {
				erg[n][n] = 0;
				double temp_d = 0;
				for(uint32_t t = 0; t < columns; t++)
					temp_d += erg[t][n];
				if(temp_d <  1e-100 && temp_d > -1e-100) {
					if(ausgabe == 1)
						std::cout << "Die Determinante der Matrix ist: " << determinante << std::endl;
					return 0;
				}
			}
			double faktor = erg[i+1][n]/erg[n][n];
			
			for(uint32_t j = 0; j < columns; j++) {
				erg[i+1][j] = erg[i+1][j]-(faktor*erg[n][j]);
			}
		}
	}
			
	// =======================
	// Determinante berechnen:
	// =======================
	for(uint32_t i = 0; i < rows; i++)
		determinante *= erg[i][i];
	
	if(ausgabe == 1)
		std::cout << "Die Determinante der Matrix ist: " << determinante << std::endl;
	//std::cout << "Die Determinante der Matrix ist: " << determinante << std::endl;
	
	return determinante;
}

mml::string mml::rechner::matrix_inverse(mml::string matrix, bool ausgabe) {
		std::size_t rows = 0; // Zeile Matrix
	std::size_t columns = 1; // Spalte Matrix
	std::size_t temp1 = 0;
	std::size_t temp2 = 0;
	mml::string temp = "";
	mml::string		ergebnis = "";
	
	// Fehlerkorrektur, falls Anfangs und Endklammern fehlen
	if(matrix[1] != '[')
		matrix = "[" + matrix.str() + "]";
	
	// =============================
	// Größe der Matrix bestimmen:
	// =============================
	// Anzahl Zeilen
	for(uint32_t i = 1; i < matrix.size(); i++) {
		if(matrix[i] == '[')
				rows++;
		
	}
	
	// Anzahl Spalten	
	temp1 = 1;
	temp2 = matrix.find(']');
	temp = matrix.sub(temp1,temp2);
	
	for(uint32_t i = 0; i < temp.size(); i++)
		if(temp[i] == ',')
			columns++;
	
	// Determinante für spätere Berechnung bestimmen:
	double det = matrix_determinante(matrix,false);
	if(det == 0)
		mml::shell::warn("| Matrix ist singular");
	
	// ===================
	// Adjunkte berechnen:
	// ===================
	matrix = matrix_adjunct(matrix,false);
		
	// ===================================
	//Umwandlung des Strings in ein Array:
	// ===================================
	double mat[rows][columns];
	double inv[rows][columns];	
	// Erste Klammern löschen:
	matrix = matrix.substr(1);
	
	// Werte zuweisen Matrix
	for(uint32_t i = 0; i < rows; i++) {
		temp1	= matrix.find('[');
		temp2	= matrix.find(']');
		temp	= matrix.sub(temp1+1,temp2-1);
		matrix = matrix.substr(temp2+2);
		
		for(uint32_t j = 0; j < columns; j++) {
			if(temp.exist(",")) {
				mat[i][j] = mml::atof((temp.sub(0,temp.find(',')-1)).str());
				temp = temp.substr(temp.find(',')+1);
			}
			else {
				mat[i][j] = temp.atof();
			} 
		}
	}
	
	// ==================
	// Inverse berechnen:
	// ==================
	for(uint32_t i = 0; i < rows; i++) {
		for(uint32_t j = 0; j < columns; j++) {
			inv[i][j] = (1/det) * (mat[i][j]);
		}
	}
	
	// =============================
	// Ergebnis in String umwandeln:
	// =============================
	for(uint32_t i = 0; i < columns; i++) {
		ergebnis += "[";
		for(uint32_t j = 0; j < rows; j++) {
				// Korrektur von std::to_string, da dies min. 8 Nachkommastellen anhängt
			temp = inv[i][j];
			while(temp[temp.size()-1] == '0')
				temp = temp.sub(0,temp.size()-2);
	
			// Korrektur, wenn eine ganze Zahl vorhanden
			if(temp[temp.size()-1]== '.')
				temp = temp.sub(0,temp.size()-2);
			
			ergebnis += temp;
			if(j < rows-1)
				ergebnis += ",";
			
		}
		ergebnis += "],";
	}
	
	ergebnis = ergebnis.substr(0,ergebnis.size()-2) + "]";
	
	if(ausgabe) {
		std::cout << "Das Inverse der Matrix ist: " << std::endl;
		matrix_print(ergebnis);
	}
	// Fehlerkorrektur, falls Anfangs und Endklammern fehlen
	if(ergebnis[1] != '[')
		ergebnis = "[" + ergebnis.str() + "]";
	return ergebnis;
}



mml::string mml::rechner::matrix_multiply(mml::string matrix1, mml::string matrix2, bool ausgabe) {
	std::size_t		rows1		= 0; // Zeile Matrix 1
	std::size_t		rows2		= 0; // Zeile Matrix 2
	std::size_t		columns1	= 1; // Spalte Matrix 1
	std::size_t		columns2	= 1; // Spalte Matrix 2
	std::size_t		temp1		= 0;
	std::size_t		temp2		= 0;
	mml::string		temp		= "";
	mml::string		ergebnis		= "";	// Ergebnis für return
	
	// =================================================
	// Korrektur, wenn Matrix nicht mit [[ oder ]] endet
	// =================================================
	if(matrix1[1] != '[')
		matrix1 = "[" + matrix1.str();
	if(matrix1[matrix1.size()-2] != ']')
		matrix1 = matrix1.str() + "]";

	if(matrix2[1] != '[')
		matrix2 = "[" + matrix2.str();
	if(matrix2[matrix2.size()-2] != ']')
		matrix2 = matrix2.str() + "]";

	// =============================
	// Größe der Matrix 1 bestimmen:
	// =============================
	// Anzahl Zeilen
	for(uint32_t i = 1; i < matrix1.size(); i++) {
		if(matrix1[i] == '[')
				rows1++;
		
	}
	// Anzahl Spalten	
	temp1 = 1;
	temp2 = matrix1.find(']');
	temp = matrix1.sub(temp1,temp2);
	
	for(uint32_t i = 0; i < temp.size(); i++)
		if(temp[i] == ',')
			columns1++;
		
	// =============================
	// Größe der Matrix 2 bestimmen:
	// =============================
	// Anzahl Zeilen
	for(uint32_t i = 1; i < matrix2.size(); i++) {
		if(matrix2[i] == '[')
				rows2++;
		
	}
	// Anzahl Spalten	
	temp1 = 1;
	temp2 = matrix2.find(']');
	temp = matrix2.sub(temp1,temp2);
	
	for(uint32_t i = 0; i < temp.size(); i++)
		if(temp[i] == ',')
			columns2++;
	// ===============================
	// Überprüfen, ob Multiplikation möglich
	// ===============================
	if(columns1 != rows2)
		mml::shell::warn("| Multiplikation nicht möglich!");	
	
	// ===================================
	//Umwandlung des Strings in ein Array:
	// ===================================
	double mat1[rows1][columns1];
	double mat2[rows2][columns2];
	double mat3[rows1][columns2];
	
	// Erste Klammern löschen:
	matrix1 = matrix1.substr(1);
	matrix2 = matrix2.substr(1);
	
	// Werte zuweisen Matrix1
	for(uint32_t i = 0; i < rows1; i++) {
		temp1	= matrix1.find('[');
		temp2	= matrix1.find(']');
		temp	= matrix1.sub(temp1+1,temp2-1);
		matrix1 = matrix1.substr(temp2+2);
		
		for(uint32_t j = 0; j < columns1; j++) {
			if(temp.exist(",")) {
				mat1[i][j] = mml::atof((temp.sub(0,temp.find(',')-1)).str());
				temp = temp.substr(temp.find(',')+1);
			}
			else {
		
				mat1[i][j] = temp.atof();
		
			} 
		}
	}

	// Werte zuweisen Matrix2
	for(uint32_t i = 0; i < rows2; i++) {
		temp1	= matrix2.find('[');
		temp2	= matrix2.find(']');
		temp	= matrix2.sub(temp1+1,temp2-1);
		matrix2 = matrix2.substr(temp2+2);
		
		for(uint32_t j = 0; j < columns2; j++) {
			if(temp.exist(",")) {
				mat2[i][j] = mml::atof((temp.sub(0,temp.find(',')-1)).str());
				temp = temp.substr(temp.find(',')+1);
			}
			else {
				mat2[i][j] = temp.atof();
				break;
			}
			
		}
	}
	
	// =====================
	// Matrixmultiplikation:
	// =====================
	for(uint32_t m = 0; m < rows1; m++) {
		for(uint32_t n = 0; n < columns2; n++) {
			double temp_d = 0;
			for(uint32_t i = 0; i < rows2; i++) {
					temp_d += mat1[m][i]*mat2[i][n];
			}
			mat3[m][n] = temp_d;
		}
	}

	// =============================
	// Ergebnis in String umwandeln:
	// =============================
	for(uint32_t i = 0; i < rows1; i++) {
		ergebnis += "[";
		for(uint32_t j = 0; j < columns2; j++) {
				// Korrektur von std::to_string, da dies min. 8 Nachkommastellen anhängt
			temp = mat3[i][j];
			while(temp[temp.size()-1] == '0')
				temp = temp.sub(0,temp.size()-2);
	
			// Korrektur, wenn eine ganze Zahl vorhanden
			if(temp[temp.size()-1]== '.')
				temp = temp.sub(0,temp.size()-2);
			
			ergebnis += temp;
			if(j < columns2-1)
				ergebnis += ",";
			
		}
		ergebnis += "],";
	}
	ergebnis = ergebnis.substr(0,ergebnis.size()-2) + "]";
	
	// =============================
	// Ergebnis formatiert ausgeben:
	// =============================
	if(ausgabe)
		matrix_print(ergebnis);
	
	return ergebnis;
}

void mml::rechner::matrix_print(mml::string matrix) {
	std::size_t rows = 0;
	std::size_t columns = 1;
	std::size_t temp1 = 0;
	std::size_t temp2 = 0;
	mml::string temp = "";
	
	// Fehlerkorrektur, falls Anfangs und Endklammern fehlen
	if(matrix[1] != '[')
		matrix = "[" + matrix.str() + "]";
	
	// =============================
	// Größe der Matrix bestimmen:
	// =============================
	// Anzahl Zeilen
	for(uint32_t i = 1; i < matrix.size(); i++) {
		if(matrix[i] == '[')
				rows++;
		
	}
	// Anzahl Spalten	
	temp1 = 1;
	temp2 = matrix.find(']');
	temp = matrix.sub(temp1,temp2);
	
	for(uint32_t i = 0; i < temp.size(); i++)
		if(temp[i] == ',')
			columns++;
		
	
	// ===================================
	//Umwandlung des Strings in ein Array:
	// ===================================
	double mat[rows][columns];
	
	// Erste Klammern löschen:
	matrix = matrix.substr(1);
	
	// Werte zuweisen Matrix1
	for(uint32_t i = 0; i < rows; i++) {
		temp1	= matrix.find('[');
		temp2	= matrix.find(']');
		temp	= matrix.sub(temp1+1,temp2-1);
		matrix = matrix.substr(temp2+2);
		
		for(uint32_t j = 0; j < columns; j++) {
			if(temp.exist(",")) {
				mat[i][j] = mml::atof((temp.sub(0,temp.find(',')-1)).str());
				temp = temp.substr(temp.find(',')+1);
			}
			else {
		
				mat[i][j] = temp.atof();
		
			} 
		}
	}
	
	// Anzahl Stellen der grössten Zahl bestimmen
	uint32_t digit[columns] = {0};
	for(uint32_t i = 0; i < columns; i++) {
		for(uint32_t n = 0; n < rows; n++) {
			if(mml::functions::digits(mat[n][i]) > digit[i]) {
				digit[i] = mml::functions::digits(mat[n][i]);
			}
		}
	}

	// ========
	// Ausgabe:
	// ========
	std::cout << " ╭";
	uint32_t num_space = 0; // Number of spaces in each column
	for (uint32_t i = 0; i < columns; i++)
		num_space += digit[i]+1;
	for (uint32_t i = 0; i < num_space; i++)
		std::cout << " ";
        std::cout << " ╮" << std::endl;
	for(uint32_t i = 0; i < rows; i++) {
		std::cout << " │";
		
		for(uint32_t j = 0; j < columns; j++) {
			// Korrektur damit nicht -0 ausgegeben wird
			if(mat[i][j] == -0)
				mat[i][j] = 0;

			for(uint32_t n = mml::functions::digits(mat[i][j]); n <= digit[j]; n++)
				std::cout << " ";
				
			std::cout << mat[i][j];
		}
		std::cout << " │" << std::endl;	
	}
	std::cout << " ╰";
	for (uint32_t i = 0; i < num_space; i++)
		std::cout << " ";
	std::cout <<  " ╯" << std::endl;
	
}

mml::string mml::rechner::matrix_smaller(mml::string matrix, uint32_t row, uint32_t column, bool ausgabe) {
	std::size_t rows = 0; // Zeile Matrix
	std::size_t columns = 1; // Spalte Matrix
	std::size_t temp1 = 0;
	std::size_t temp2 = 0;
	mml::string temp = "";
	mml::string		ergebnis = "";
	
	// Fehlerkorrektur, falls Anfangs und Endklammern fehlen
	if(matrix[1] != '[')
		matrix = "[" + matrix.str() + "]";
	
	// =============================
	// Größe der Matrix bestimmen:
	// =============================
	// Anzahl Zeilen
	for(uint32_t i = 1; i < matrix.size(); i++) {
		if(matrix[i] == '[')
				rows++;
		
	}
	
	// Anzahl Spalten	
	temp1 = 1;
	temp2 = matrix.find(']');
	temp = matrix.sub(temp1,temp2);
	
	for(uint32_t i = 0; i < temp.size(); i++)
		if(temp[i] == ',')
			columns++;
	
	// ===================================
	//Umwandlung des Strings in ein Array:
	// ===================================
	double mat[rows][columns];
	double red[rows-1][columns-1];
	
	// Erste Klammern löschen:
	matrix = matrix.substr(1);
	
	// Werte zuweisen Matrix
	for(uint32_t i = 0; i < rows; i++) {
		temp1	= matrix.find('[');
		temp2	= matrix.find(']');
		temp	= matrix.sub(temp1+1,temp2-1);
		matrix = matrix.substr(temp2+2);
		
		for(uint32_t j = 0; j < columns; j++) {
			if(temp.exist(",")) {
				mat[i][j] = mml::atof((temp.sub(0,temp.find(',')-1)).str());
				temp = temp.substr(temp.find(',')+1);
			}
			else {
				mat[i][j] = temp.atof();
			} 
		}
	}
	
	// ==========================================
	// rowte Zeile und columnte Spalte entfernen:
	// ==========================================
	int u = 0;
	
	for(uint32_t i = 0; i < rows-1; i++) {
		if(i == row) {
			u = 1;
		}
		int t = 0;
		for(uint32_t j = 0; j < columns-1; j++) {
			if(j == column) {
				t = 1;
			}
			red[i][j] = mat[i+u][j+t];
		}
	}
	
	// =============================
	// Ergebnis in String umwandeln:
	// =============================
	for(uint32_t i = 0; i < columns-1; i++) {
		ergebnis += "[";
		for(uint32_t j = 0; j < rows-1; j++) {
				// Korrektur von std::to_string, da dies min. 8 Nachkommastellen anhängt
			temp = red[i][j];
			while(temp[temp.size()-1] == '0')
				temp = temp.sub(0,temp.size()-2);
	
			// Korrektur, wenn eine ganze Zahl vorhanden
			if(temp[temp.size()-1]== '.')
				temp = temp.sub(0,temp.size()-2);
			
			ergebnis += temp;
			if(j < rows-2)
				ergebnis += ",";
			
		}
		ergebnis += "],";
	}
	ergebnis = ergebnis.substr(0,ergebnis.size()-2) + "]";

	if(ausgabe)
		matrix_print(ergebnis);
	// Fehlerkorrektur, falls Anfangs und Endklammern fehlen
	if(ergebnis[1] != '[')
		ergebnis = "[" + ergebnis.str() + "]";
	return ergebnis;
	
}


mml::string mml::rechner::matrix_transposed(mml::string matrix, bool ausgabe) {
	
	std::size_t rows = 0; // Zeile Matrix
	std::size_t columns = 1; // Spalte Matrix
	std::size_t temp1 = 0;
	std::size_t temp2 = 0;
	mml::string temp = "";
	mml::string		ergebnis = "";
	
	// Fehlerkorrektur, falls Anfangs und Endklammern fehlen
	if(matrix[1] != '[')
		matrix = "[" + matrix.str() + "]";
	
	// =============================
	// Größe der Matrix bestimmen:
	// =============================
	// Anzahl Zeilen
	for(uint32_t i = 1; i < matrix.size(); i++) {
		if(matrix[i] == '[')
				rows++;
		
	}
	
	// Anzahl Spalten	
	temp1 = 1;
	temp2 = matrix.find(']');
	temp = matrix.sub(temp1,temp2);
	
	for(uint32_t i = 0; i < temp.size(); i++)
		if(temp[i] == ',')
			columns++;
	
	// ===================================
	//Umwandlung des Strings in ein Array:
	// ===================================
	double mat[rows][columns];
	double tra[columns][rows];
	
	// Erste Klammern löschen:
	matrix = matrix.substr(1);
	
	// Werte zuweisen Matrix
	for(uint32_t i = 0; i < rows; i++) {
		temp1	= matrix.find('[');
		temp2	= matrix.find(']');
		temp	= matrix.sub(temp1+1,temp2-1);
		matrix = matrix.substr(temp2+2);
		
		for(uint32_t j = 0; j < columns; j++) {
			if(temp.exist(",")) {
				mat[i][j] = mml::atof((temp.sub(0,temp.find(',')-1)).str());
				temp = temp.substr(temp.find(',')+1);
			}
			else {
				mat[i][j] = temp.atof();
			} 
		}
	}
	
	// ==============
	// Transponieren:
	// ==============
	for(uint32_t i = 0; i < rows; i++) {
		for(uint32_t j = 0; j < columns; j++) {
			tra[j][i] = mat[i][j];
		}
	}
	// =============================
	// Ergebnis in String umwandeln:
	// =============================
	for(uint32_t i = 0; i < columns; i++) {
		ergebnis += "[";
		for(uint32_t j = 0; j < rows; j++) {
				// Korrektur von std::to_string, da dies min. 8 Nachkommastellen anhängt
			temp = tra[i][j];
			while(temp[temp.size()-1] == '0')
				temp = temp.sub(0,temp.size()-2);
	
			// Korrektur, wenn eine ganze Zahl vorhanden
			if(temp[temp.size()-1]== '.')
				temp = temp.sub(0,temp.size()-2);
			
			ergebnis += temp;
			if(j < rows-1)
				ergebnis += ",";
			
		}
		ergebnis += "],";
	}
	ergebnis = ergebnis.substr(0,ergebnis.size()-2) + "]";
	if(ausgabe)
		matrix_print(ergebnis);
	// Fehlerkorrektur, falls Anfangs und Endklammern fehlen
	if(ergebnis[1] != '[')
		ergebnis = "[" + ergebnis.str() + "]";
	return ergebnis;
	
}




