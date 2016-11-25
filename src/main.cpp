#include <iostream>
#include <fstream>
#include <vector>

#include <map>

std::string lower(std::string string) {
  std::locale loc;

  for (std::string::size_type i = 0; i < string.length(); ++i) {
    string[i] = std::tolower(string[i],loc);
  }

  return string;
}

void writeOut(std::map<std::string, int> words, std::ofstream& ofile) {
  ofile<<"word,freq\n";
  for (auto it = words.begin(); it != words.end(); ++it) {
    ofile<<it->first<<","<<it->second<<"\n";
  }
}

void makeStopWords(std::string SWFile, std::vector<std::string> &list) {
  std::ifstream file(SWFile);
  if (file) {
    std::string stopword;
    while (file>>stopword) {
      list.push_back(stopword);
    }
  }
}

bool isStopWord(std::string word, std::vector<std::string>& stopwords) {
  for (auto it = stopwords.begin(); it != stopwords.end(); ++it) {
    if (*it == word) return true;
  }
  return false;
}

std::vector<std::string> sw;

int main(){
  std::ifstream file("transcripts/debate_1");
  std::ofstream ofile("data/debate_1.csv");

  std::map< std::string, int > words;

  makeStopWords("misc/stopwords", sw);

  if (file) {
    std::string word;
    int count = 0;
    while ( file >> word ) {
      //to lower case and remove punctuation
      word = lower(word);
      std::string text;
      std::remove_copy_if(word.begin(), word.end(), std::back_inserter(text),std::ptr_fun<int,int>(&std::ispunct));
      word = text;

      //check if stopword or a number or blank
      if (isStopWord(word,sw) || isdigit(word[0]) || word.length() == 0) {
        std::cout<<word<<std::endl;
        continue;
      }

      count++;


      //checks if its in the map if not it adds it with val = 0
      if ( words[word] == 0 ){};
      //increments val (new word currently has val of 0)
      words[word]++;
    }
    std::cout<<count<<std::endl;
    std::cout<<words.size()<<std::endl;
    std::cout<<words.begin()->first<<std::endl;
    writeOut(words, ofile);
  }

}
