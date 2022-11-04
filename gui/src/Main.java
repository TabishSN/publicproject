import javax.swing.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

public class Main implements ActionListener {

    private static JLabel userLabel;
    private static JTextField userText;
    private static JLabel passLabel;
    private static JPasswordField passwordText;
    private static JButton button;
    private static JLabel success;


    public static void main(String[] args) {
        JPanel panel = new JPanel();
        JFrame frame = new JFrame();
        frame.setSize(350, 200);
        frame.setDefaultCloseOperation(WindowConstants.EXIT_ON_CLOSE);
        frame.add(panel);

        panel.setLayout(null);

        userLabel = new JLabel("User");
        userLabel.setBounds(10, 20, 80, 25);
        panel.add(userLabel);

        userText = new JTextField(20);
        userText.setBounds(100, 20, 165, 25);
        panel.add(userText);

        passLabel = new JLabel("Password");
        passLabel.setBounds(10, 50, 80, 25);
        panel.add(passLabel);

        passwordText = new JPasswordField();
        passwordText.setBounds(100, 50, 165, 25);
        panel.add(passwordText);

        button = new JButton("Login");
        button.setBounds(10, 80, 80, 25);
        panel.add(button);

        success = new JLabel("");
        success.setBounds(10, 110, 300, 25);
        panel.add(success);
        button.addActionListener(new Main());

        success.setText("");

        frame.setVisible(true);



    }

    @Override
    public void actionPerformed(ActionEvent e) {
        String user = userText.getText();
        String password = passwordText.getText();
        System.out.println(user + "," + password);

        if (user.equals("Tabish") && password.equals("12345")){
            System.out.println("Login Successful");
        }
        else{
            System.out.println("Incorrect Credentials");
        }

    }
}