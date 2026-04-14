import java.util.Scanner;

public class Somador {

    public static int somarDigitos(int n) {
        return somarDigitos(n, 0);
    }

    private static int somarDigitos(int n, int soma) {
        int resp;

        if (n < 10) {
            resp = n;
        } else {
            resp = (n % 10) + somarDigitos(n / 10, soma);
        }

        return resp;
    }

    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);

        while (sc.hasNextInt()) {
            int numero = sc.nextInt();
            
            if (numero < 0) numero *= -1;

            int resultado = somarDigitos(numero);
            System.out.println(resultado);
        }

        sc.close();
    }
}