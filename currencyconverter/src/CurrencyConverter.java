import java.util.*;
import java.text.DecimalFormat;

public class CurrencyConverter {

    public static void main(String[] args) {

        double amount, dollar, pound, code, euro, yen;

        DecimalFormat f = new DecimalFormat("##.##");

        Scanner sc = new Scanner(System.in);

        System.out.println("hi, Welcome to the Currency Converter!");

        System.out.println("which currency You want to Convert ? ");

        System.out.println("1:Dollar \t2:Pound \n3:Euro \t4:Yen ");
        code = sc.nextInt();

        System.out.println("How much Money you want to convert ?");
        amount = sc.nextFloat();

        // For amounts Conversion

        if (code == 1) {
            // Dollar Conversion
            pound = amount * 0.88;
            System.out.println("Your " + amount + " Dollar is : " + f.format(pound) + " Pound");

            euro = amount * 1;
            System.out.println("Your " + amount + " Dollar is : " + f.format(euro) + " Euro");

            yen = amount * 146.62;
            System.out.println("Your " + amount + " Dollar is : " + f.format(yen) + " Yen");

        }
        else if (code == 2) {
            // Pound Conversion
            dollar = amount * 1.14;
            System.out.println("Your " + amount + " pound is : " + f.format(dollar) + " Dollar");

            euro = amount * 1.14;
            System.out.println("Your " + amount + " pound is : " + f.format(euro) + " Euro");

            yen = amount * 166.82;
            System.out.println("Your " + amount + " pound is : " + f.format(yen) + " Yen");


        } else if (code == 3) {
            // Euro Conversion
            dollar = amount * 1;
            System.out.println("Your " + amount + " euro is : " + f.format(dollar) + " Dollar");

            pound = amount * 0.88;
            System.out.println("Your " + amount + " euro is : " + f.format(pound) + " Pound");

            yen = amount * 145.26;
            System.out.println("Your " + amount + " euro is : " + f.format(yen) + " Yen");


        } else if (code == 4) {

            // Yen Conversion

            dollar = amount * 0.0068;
            System.out.println("Your " + amount + " yen is : " + f.format(dollar) + " Dollar");

            pound = amount * 0.006;
            System.out.println("Your " + amount + " yen is : " + f.format(pound) + " Pound");

            euro = amount * 0.0068;
            System.out.println("Your " + amount + " yen is : " + f.format(euro) + " Euro");

        }
        else {
            System.out.println("Invalid input");
        }

        System.out.println("Thank you for choosing our Example Programs");
    }

}