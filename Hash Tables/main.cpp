/*
 * Name: Carter Brewer
 * Date Submitted: 1 March 2021
 * Lab Section: 001
 * Assignment Name: Lab 5 - Spell Checker Using A Hash Table
 */
 
 #include "stringset.h"
 #include <iostream>
 #include <fstream>
 
 void testStringset(Stringset& words);
 void loadStringset(Stringset& words, string filename);
 vector<string> spellcheck(const Stringset& words, string word);
 
 int main()
 {
     Stringset words;
     vector<string> alternatives;
     int count = 0;
     loadStringset(words, "wordlist.txt");
     alternatives = spellcheck(words, "lake");
	 for (int i = 0; i < alternatives.size(); ++i)
	 {
		 if (alternatives[i] == "bake" ||
			 alternatives[i] == "cake" ||
			 alternatives[i] == "fake" ||
			 alternatives[i] == "make" ||
			 alternatives[i] == "rake" ||
			 alternatives[i] == "sake" ||
			 alternatives[i] == "take" ||
			 alternatives[i] == "wake" ||
			 alternatives[i] == "leke" ||
			 alternatives[i] == "like" ||
			 alternatives[i] == "lace" ||
			 alternatives[i] == "lade" ||
			 alternatives[i] == "lame" ||
			 alternatives[i] == "lane" ||
			 alternatives[i] == "late" ||
			 alternatives[i] == "lave" ||
			 alternatives[i] == "laze" ||
			 alternatives[i] == "laky")
		 {
			 count++;
		 }
	 }
     cout << "Count = " << count << endl;
     //testStringset(wordlist);
     return 0;
 }
 
 void testStringset(Stringset& words)
 {
     string choice;
     string word;
     do
     {
         cout << "I: insert word" << endl;
         cout << "F: find word" << endl;
         cout << "R: remove word" << endl;
         cout << "P: print words in stringset" << endl;
         cout << "Q: quit" << endl;
         cin >> choice;
         switch (choice[0])
         {
             case 'I':
             case 'i':
                cout << "Enter word to insert: ";
                cin >> word;
                words.insert(word);
                break;
             case 'F':
             case 'f':
                cout << "Enter word to find: ";
                cin >> word;
                if (words.find(word))
                {
                    cout << word << " in stringset" << endl;
                }
                else
                {
                    cout << word << " not in stringset" << endl;
                }
                break;
             case 'R':
             case 'r':
                cout << "Enter word to remove: ";
                cin >> word;
                words.remove(word);
                break;
             case 'P':
             case 'p':
                vector<list<string>> t = words.getTable();
                int numWords = words.getNumElems();
                int tSize = words.getSize();
                cout << "Size = " << words.getSize() << endl;
                for(int i=0; i<tSize; ++i)
                {
                    list<string>::iterator pos;
                    for (pos = t[i].begin(); pos != t[i].end(); ++pos)
                    {
                        //cout << "table[" << i << "] = " << *pos << endl;
                        cout << *pos << endl;
                    }
                }
                cout << "Words: " << numWords << endl;
         }
     } while (choice[0] != 'Q' && choice[0] != 'q');
 }
 
 void loadStringset(Stringset& words, string filename)
 {
     //Implement this function
	 fstream file;
	 file.open(filename);
     string word;
     while (getline(file, word))
     {
         words.insert(word);
         if (!words.find (word)){ file >> word; }
         
     }
 }
 
 vector<string> spellcheck(const Stringset& words, string word)
 {
     
     /*cout << "INSIDE SPELLCHECK" << endl;*/
     //Implement this function
     list<char> alphabet = { 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z' };
     string altWordTester = word;
     vector<string> testReturn;
     if (words.find(word))
     {
         /*cout << "INSIDE IF" << endl;*/

         list<char>::iterator posAlphabet;
         
		for (int i = 0; i < word.size(); i++)
		{
			for (posAlphabet = alphabet.begin(); posAlphabet != alphabet.end(); posAlphabet++)
			{
                altWordTester[i] = *posAlphabet;
				if (words.find(altWordTester) && altWordTester != word)
				{
					testReturn.push_back(altWordTester);
                    cout << altWordTester << endl;
				}
                
			}
            altWordTester = word;
		}
     }
     return testReturn;
 }