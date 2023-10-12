#include <iostream>
#include <string>
#include <vector>
#include <fstream>

const char* SIDEBAR_PATH = "/var/www/obs-web.rs.umbc.edu/data/pages/sidebar.txt";
const char* BODY_TAG = "<body>";
const char* BACKUP_PATH = "/home/gabriek1/backup.txt";

//NULL exists as a placeholder to avoid off-by-one errors
//and easier use
std::vector<std::string> months = {"NULL", "January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December"};

//Creates backup of the sidebar file just in case something bad happens during editing
void createBackup(const std::vector<std::string>& lines){
   std::ofstream backupFile;
   backupFile.open(BACKUP_PATH);

   for(std::string i : lines){
      backupFile << i << "\n";
   }
   backupFile.close();
}


/// @brief Processes parameter into an appropriate html line (hyperlink of the blog)
/// @param blogPost file name of the blog, formatted to remove .txt 
/// @return html line
std::string createStringForBlogEntry(const std::string& blogPost){  
   std::string htmlLine;

   std::string p1 = "<p><a class=\"wikilink1\" data-wiki-id=\"blog:";
   std::string p2 = "\" href=\"/doku.php?id=blog:";
   std::string p3 = "\" title=\"blog:";
   std::string p4 = "\">";
   std::string p5 = "</a></p>";

   htmlLine = p1 + blogPost + p2 + blogPost + p3 + blogPost + p4 + blogPost + p5;

   return htmlLine;
} 


/// @brief Appends to the vector of lines the needed html lines to create a tab-button element
/// @param lines Vector of html lines of sidebar
/// @param month month that blog was created in, in Alpha form
/// @param year Year that blog was made in, format: YYYY
/// @param lineNum Number of line, or vector element, to insert to
/// @return formatted line(s) of html
std::string createStringForMonth(const std::string& month, const std::string& year){
   std::string htmlLine;

   std::string p1 = "<div class=\"tab-button\" onclick=\"toggleTab('";
   std::string p2 = "')\">";
   std::string p3 = "</div>\n";
   std::string p4 = "<div class=\"tab-content\" id=\"";
   std::string p5 = "\">\n";
   std::string p6 = "</div>";

   htmlLine = p1 + month + year + p2 + month + p3 + p4 + month + year + p5 + p6;

   return htmlLine;
}


//loads the file into a vector of strings
//Each vector element stores one line of html code
std::vector<std::string> loadFile(std::string fileName){
   std::ifstream file(fileName);

   if(!file.is_open()){
      std::cerr << "Failed to open file " << fileName << "\n";
      exit(0);
   }

   //stores lines of html code
   std::vector<std::string> lines;
   std::string line;

   while(std::getline(file, line)){
      lines.push_back(line);
   }

   file.close();
   
   return lines;
}

//finds a string (month name + year, format: monthYYYY) in a line of code
//and returns the line number
//if not found returns -1 
int findLine(const std::vector<std::string>& lines, std::string month, std::string year = ""){
   for(int i = 0; i < lines.size(); ++i){
      if(lines[i].find(month + year) != std::string::npos){
         //returns the line number where the string was found in
         return i;
      }
   }

   //if not found, returns -1
   return -1;
}


/// @brief Inserts given line string into vector of lines
/// @param lines 
/// @param line 
/// @param lineNum 
void insertLine(std::vector<std::string>& lines, std::string fileName, std::string action){
   std::string fileNameCopy = fileName;

   //getting the number of the month from the filename
   std::string year;
   std::string monthNum;
   monthNum = fileName[4];
   monthNum += fileName[5];
   fileName.resize(4);
   year = fileName;

   int lineNum = 0;

   if(action == "CREATE"){
      //if the month exists on there
      if(findLine(lines, months[std::stoi(monthNum)], year) != -1){
         lineNum = findLine(lines, months[std::stoi(monthNum)], year) + 2;
         lines.insert(lines.begin() + lineNum, createStringForBlogEntry(fileNameCopy));
      }else{
         //if month doesn't exist, or month doesn't exist for set year
         std::string line = createStringForMonth(months[std::stoi(monthNum)], year);
         std::string line1 = "", line2 = "", line3 = "";
         int index = 0; //which line var to store to 

         //splitting string according to newlines
         for(char i : line){
            if(i != '\n'){
               if(index == 0){
                  line1 += i;
               }else if(index == 1){
                  line2 += i;
               }else{
                  line3 += i;
               }
            }else{
               index++;
            }
         }

         lineNum = findLine(lines, BODY_TAG);
         lineNum++;
         lines.insert(lines.begin() + lineNum, line1);
         lineNum++;
         lines.insert(lines.begin() + lineNum, line2);
         lineNum++;
         lines.insert(lines.begin() + lineNum, line3);
         lines.insert(lines.begin() + lineNum, createStringForBlogEntry(fileNameCopy));
      }
   }else if(action == "DELETE"){
      if(findLine(lines, fileNameCopy) != -1){
         lineNum = findLine(lines, fileNameCopy);
         lines.erase(lines.begin() + lineNum);

         if(lines[lineNum] == "</div>"){
            if(lines[lineNum - 1].find("<div class=\"tab-content\"") != std::string::npos){
               lines.erase(lines.begin() + lineNum - 2);
               lines.erase(lines.begin() + lineNum - 2);
               lines.erase(lines.begin() + lineNum - 2);
            }
         }
      }
   }
}

//outputs to a given file
void outputToFile(std::string fileToEdit, const std::vector<std::string>& lines){
   std::ofstream file;
   file.open(fileToEdit);

   if(!file.is_open()){
      std::cerr << "Unable to open file for editing.\n";
      return;
   }

   for(std::string i : lines){
      file << i << "\n";
   }

   file.close();
}

int main(int argc, char **argv){
   std::string filename;
   std::string action;
   
   if(argc >= 3){
      filename = argv[1];
      filename.resize(8);//changing the size of the filename to ommit the .txt extension
      action = argv[2];
   }else{
      exit(0);
   }

   std::vector<std::string> linesOfCode = loadFile(SIDEBAR_PATH);

   createBackup(linesOfCode);
   insertLine(linesOfCode, filename, action);
   outputToFile(SIDEBAR_PATH, linesOfCode);
   
   return 0;
