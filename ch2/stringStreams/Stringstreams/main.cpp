#include <iostream>
#include <sstream>
#include <array>
#include <string>


template <size_t SIZE>
auto test_1(std::array<int, SIZE> & ar, std::stringstream & ss) -> void{

    ss << "30 25 70.3";
    ss << "EtwasText";

    ss >> ar[0];
    ss >> ar[1];
    ss >> ar[2];
    ss >> ar[3];   
}

template <size_t SIZE>
auto test_2(std::array<int, SIZE> & ar, std::stringstream & ss) -> void{

    ss << "30 25";
    ss << "EtwasText"; // gleiches Ergebnis auch mt  ss << "E" oder ss << 'E';
    ss << "52";

    ss >> ar[0];
    ss >> ar[1];
    ss >> ar[2];
    ss >> ar[3];   
}

template <size_t SIZE>
auto test_3(std::array<int, SIZE> & ar, std::stringstream & ss) -> void{

    std::string str{};

    ss << "30 25";
    ss << "EtwasText "; // ATTENTION: si apres le text il n'y a pas un espace alors l'extration ne se passe pas corretement. 52 va etre collé a EtwasText
    ss << "EtwasText"; // führt zu Fehler !!!!
    ss << "52";

    ss >> ar[0];
    ss >> ar[1];
    ss >> str;
    ss >> ar[2]; 

    std::cout << "str = " << str << std::endl;  
}

template <size_t SIZE>
auto test_4(std::array<int, SIZE> & ar, std::stringstream & ss) -> void{

  std::cout << "In  test_4 -> block_test_4 =  ";
    
    std::string str{};
    float f{-41.7};

#define block_test_4 4

#if(block_test_4 == 1) // OK
    std::cout << block_test_4 << std::endl;
    ss << "30 25 70.3 "; // espace a la fin important. Si non EtwasText de la ligne suivante serra collé a 70.3 (resulta 70.3EtwasText) et quand on cherchant a extraire un float a partir du resultat, cela ne fonctionne pa. Voir block_test_4 ==2
    ss << "EtwasText";

    ss >> ar[0];
    ss >> ar[1];
    ss >> f;
    ss >> str;

#elif(block_test_4 == 2) // MOYENNEMENT OK . faire attention au espace: soit a la fin de EtwasText ou au debut de 85.5
    std::cout << block_test_4 << std::endl;
    ss << "30 25 70.3"; // contrairement a block_test_4 == 2 on na pas d'espace a la fin. Par contre on cherche dabor a extair un string (on aurra 70.3EtwasText). Pour L'extration du float on aurra f = 41. car le string_stream a completement été lu et il n'ya plus rien a extraire  si la ligne ss << "85.5" n'est pas presente
    ss << "EtwasText";  // mettreun espace a la fin pour que la prochaine donnée a garder dans ss ne soit pas directement collé a EtwasText ou bien mettre un espace directement au debut de la prochaine donnée a garder dans ss 
    ss << " 85.5";

    ss >> ar[0];
    ss >> ar[1];
    ss >> str;
    ss >> f;

#elif(block_test_4 == 3) // NOT OK
    std::cout << block_test_4 << std::endl;
    ss << "30 25 ";    // espace a la fin important. Si non 70.3 de la ligne suivante est inserée dans ss en etant collé a 25 (donc on a 2570.3) et l'orde de l'extraction on a 2570
    ss << "70.3";      // comme il n'y a pas d'espace a la fin de 70.3 et au debut de EtwasText alors les 2
    ss << "EtwasText"; // données seront colées et interpretées comme une seul. le resutat est 70.3EtwasText 
                       // avec  l'ordre d'extration ci dessous, on ne pourra pa extraire un float a partir du resultat. Par contre on pourrai extraire un string  comme au cas block_test_4 ==2
    ss >> ar[0];
    ss >> ar[1];
    ss >> f;
    ss >> str; 

#elif(block_test_4 == 4) // OK
    std::cout << block_test_4 << std::endl;
    ss << "70.3 "; // espace a la fin important ou au debut de la ligne suivante. Si non 30 de la ligne suivante est inserée dans ss en etant collé a 70.3 (donc on a 70.330) et l'orde de l'extraction on a 70.33 
    ss << "30 25";
    ss << "EtwasText";

    ss >> f;
    ss >> ar[0];
    ss >> ar[1];
    ss >> str;

#endif

    std::cout << "f = " << f << std::endl;
    std::cout << "str = " << str << std::endl; 

}



/*auto check_state_sstream(const std::stringstream & ss){
 if ( (ss.rdstate() & std::stringstream::failbit ) != 0 ) {
      std::cerr << "Error: Not all values could be extracted correctly!" << std::endl;
    }
}
*/

int main(){

  std::stringstream ss{};
  std::array<int, 4> x{};

  test_4(x, ss);

  for( const auto e : x) {
      std::cout << e << std::endl;
  }
  if ( (ss.rdstate() & std::stringstream::failbit ) != 0 ) {
      std::cerr << "Error: Not all values could be extracted correctly!" << std::endl;
  }



    return 0;
}

// Code original
/*int main(){

  std::stringstream ss;

    std::array<int, 4> x;

    ss << "30 25 70.3";
    ss << "EtwasText";

    ss >> x[0];
    ss >> x[1];
    ss >> x[2];
    ss >> x[3];

    for( const auto e : x) {
        std::cout << e << std::endl;
    }

    if ( (ss.rdstate() & std::stringstream::failbit ) != 0 ) {
      std::cerr << "Error: Not all values could be extracted correctly!" << std::endl;
    }
}*/
