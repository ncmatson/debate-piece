#include <iostream>
#include <fstream>
#include <vector>
#include <map>

void makeStopWords(std::string SWFile, std::vector<std::string> &list) {
  std::ifstream file(SWFile);
  if (file) {
    std::string stopword;
    while (file>>stopword) {
      list.push_back(stopword);
    }
  }
}

std::string lower(std::string string) {
  std::locale loc;

  for (std::string::size_type i = 0; i < string.length(); ++i) {
    string[i] = std::tolower(string[i],loc);
  }

  return string;
}

std::string processWord(std::string word) {
  word = lower(word);
  std::string text;
  std::remove_copy_if(word.begin(), word.end(), std::back_inserter(text),std::ptr_fun<int,int>(&std::ispunct));
  return text;

}

bool isStopWord(std::string word, std::vector<std::string>& stopwords) {
  for (auto it = stopwords.begin(); it != stopwords.end(); ++it) {
    if (*it == word) return true;
  }
  return false;
}

void readFrequencies(std::ifstream& file, std::map<std::string, int>& words, std::vector<std::string> sw) {
  if (file) {
    std::string word;
    while ( file >> word ) {
      //to lower case and remove punctuation
      word = processWord(word);

      //check if stopword or a number or blank
      if (isStopWord(word,sw) || isdigit(word[0]) || word.length() == 0) {continue;}

      //checks if its in the map if not it adds it with val = 0
      if ( words[word] == 0 ){}
      //increments val (new word currently has val of 0)
      words[word]++;
    }
  }
}

void writeOut(std::map<std::string, int> words, std::ofstream& ofile) {
  ofile<<"word,freq\n";
  for (auto it = words.begin(); it != words.end(); ++it) {
    ofile<<it->first<<","<<it->second<<"\n";
  }
}

void splitSpeakers(std::ifstream& file, std::vector<std::string>& clinton,
                                        std::vector<std::string>& trump,
                                        std::vector<std::string>& other) {
  if (file) {
    std::string speaker;
    std::string word;
    file>>word;//this is bad
    while (file >> word) {
      if (word == "TRUMP:") {
        trump.push_back(word);
        speaker = word;
        continue;
      }
      else if (word == "CLINTON:") {
        clinton.push_back(word);
        speaker = word;
        continue;
      }
      else if (word == "HOLT:") {
        other.push_back(word);
        speaker = word;
        continue;
      }

      word = processWord(word);

      if (speaker == "TRUMP:") {trump.push_back(word);}
      else if (speaker == "CLINTON:") {clinton.push_back(word);}
      else {other.push_back(word);}
    }
  }
}

std::vector<std::string> sw;

int main(){
  std::ifstream file("transcripts/debate_3");
  std::ofstream ofile("data/debate_3.csv");

  std::map< std::string, int > words;

  std::vector<std::string> trump;
  std::vector<std::string> clinton;
  std::vector<std::string> other;

  makeStopWords("misc/stopwords", sw);

  // splitSpeakers(file, clinton, trump, other);
  // for (auto it = other.begin(); it != other.end(); ++it){
  //   std::cout<<*it<<std::endl;
  // }

  readFrequencies(file, words, sw);

  writeOut(words, ofile);

}
