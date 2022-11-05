import java.util.Scanner;

public class Main {
    public static void main(String[] args) {
        Scanner scan = new Scanner(System.in);
        System.out.println("This will calculate your body mass index");

        System.out.println("Enter your weight in pounds: ");
        double weight = scan.nextDouble();

        System.out.println("Enter your height in inches: ");
        double height = scan.nextDouble();

        double Bmi = weight / (height * height) * 703;
        System.out.println("your BMI is" + Bmi + ".");





    }
}