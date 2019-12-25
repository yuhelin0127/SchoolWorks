import java.io.*;
import java.util.Hashtable;
import java.util.Scanner;


public class Lab19 {

    // Lab 19 TODO: 
    //  declare the variable  myDictionary

    Hashtable<String, String> myDictionary = new Hashtable<>();


    public Lab19(String pFileName) throws IOException {

        int lLineNumber = 1;
        String lFoundLines;

        File file = new File(pFileName);

        // Lab 19 TODO: 
        //   create a scanner
        //   lInputScanner = new Scanner(....);

        Scanner lInputScanner = new Scanner(file);


        // Lab 19 TODO: 
        //   instantiate myDictionary

        while (lInputScanner.hasNext()) {


            // Lab 19 TODO: 
            // get new line from file
            // split the current line into words, around regex matches of any non-word characters:
            //  ... lAllWordsInLine ...

            String currentLine = lInputScanner.nextLine();
            String[] lAllWordsInLine = currentLine.split("\\W+");

            for (int i = 0; i < lAllWordsInLine.length; i++) {

                // Lab 19 TODO: 
                // for each word, look into myDictionary if it already has been seen...
                if (!myDictionary.contains(lAllWordsInLine[i])) {
                    // if it's a new word, store the current line number
                    //    as value in the myDictionary for the new word used as key

                    String Line = Integer.toString(lLineNumber);
                    myDictionary.put(lAllWordsInLine[i].toLowerCase(), Line);

                } else {
                    // if the word is already in the dictionary,
                    //   add the the current line number to the line numbers already in the myDictionary,
                    //   i.e. modify the value associated with the key,
                    //   so that the value is updated with the current line:

                    String newLine = myDictionary.get(lAllWordsInLine[i].toLowerCase()) + ", " + Integer.toString(lLineNumber);
                    myDictionary.remove(lAllWordsInLine[i].toLowerCase());
                    myDictionary.put(lAllWordsInLine[i].toLowerCase(), newLine);

                }
            }


            lLineNumber++;
        }
        lInputScanner.close();

}// end of Lab19() constructor

    public void wordQuery(String pWord) {
        String lLines = myDictionary.get(pWord.toLowerCase());


        if (lLines != null) {
            System.out.println(pWord + " is found in lines: " + lLines);
        } else {
            System.out.println(pWord + " not found.");
        }
    }

    public static void main(String args[]) throws IOException {
        // Lab 19 TODO: 
        // read document and store its content:
        //  Lab19 mytxt = ...
        // test your methods:

        Lab19 mytxt = new Lab19("/Users/yuhelin/Desktop/C343yuhelin/lab/lab19/src/lab-19-testing.txt");

        mytxt.wordQuery("algorithm");
        mytxt.wordQuery("data");
        mytxt.wordQuery("memory");
        mytxt.wordQuery("ADT");
    }


} // end of class Lab19