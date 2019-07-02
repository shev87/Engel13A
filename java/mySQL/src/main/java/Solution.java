import java.sql.Connection;
import java.sql.DriverManager;

public class Solution {
    public static void main(String[] args) throws Exception {
        String user = "shev87";
        String password = "12345678";
        String driver = "com.mysql.jdbc.Driver";
        String urlOnline = "jdbc:mysql://db4free.net:3306/netcracker?useSSL=false";
        String url ="jdbc:mysql://localhost:3306/basevova?useSSL=false";
        Class.forName(driver);
        try(Connection connection = DriverManager.getConnection(urlOnline, user, password)){
            System.out.printf("we're connected!");
        }
    }
}
