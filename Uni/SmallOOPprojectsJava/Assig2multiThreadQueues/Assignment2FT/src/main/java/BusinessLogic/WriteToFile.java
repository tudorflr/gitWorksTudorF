package BusinessLogic;
import java.io.FileWriter;   // Import the FileWriter class
import java.io.IOException;  // Import the IOException class to handle errors

public class WriteToFile {

    public static void WriteToFile(String result) {
        try {
            FileWriter myWriter = new FileWriter("SimLog.txt");
            myWriter.write(result);
            myWriter.close();
            //System.out.println("Successfully wrote to the file.");
        } catch (IOException e) {
            System.out.println("An error occurred.");
            e.printStackTrace();
        }
    }

}
