import java.util.Scanner;

public class InversaoRecursiva {

    public static boolean ehFim(String s) {
        return s.length() == 3 && s.charAt(0) == 'F' && s.charAt(1) == 'I' && s.charAt(2) == 'M';
    }

    public static String inverterRecursivo(String s, int i) {
        String resp;

        if (i == s.length()) {
            resp = "";
        } else {
            resp = inverterRecursivo(s, i + 1) + s.charAt(i);
        }

        return resp;
    }

    public static String inverter(String s) {
        return inverterRecursivo(s, 0);
    }

    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        
        if (sc.hasNextLine()) {
            String linha = sc.nextLine();

            while (!ehFim(linha)) {
                String resultado = inverter(linha);
                System.out.println(resultado);

                if (sc.hasNextLine()) {
                    linha = sc.nextLine();
                } else {
                    linha = "FIM"; 
                }
            }
        }
        
        sc.close();
    }
}