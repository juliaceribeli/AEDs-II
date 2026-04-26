import java.util.*;

public class Senha {

    public static boolean ehFim(String s){
        return s.length() == 3 && s.charAt(0) == 'F' && s.charAt(1) == 'I' && s.charAt(2) == 'M'; 
    }
    
    public static boolean validacao(String s){
        boolean valida = false;
        boolean tam = false;
        boolean maiuscula = false;
        boolean minuscula = false;
        boolean numero = false;
        boolean carac = false;
        
        if(s.length() >= 8) {
            tam = true;
            for (int i = 0; i < s.length(); i++){
                char c = s.charAt(i);
                if(c >= 'A' && c <= 'Z') maiuscula = true;
                if(c >= 'a' && c <= 'z') minuscula = true;
                if(c >= '0' && c <= '9') numero = true;
                if(!((c >= '0' && c <= '9') || (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))) carac = true;
            }
        }

        if (tam && maiuscula && minuscula && numero && carac) valida = true;

        return valida;
    }
    public static void main(String args[]){
        
        Scanner sc = new Scanner(System.in);

        String senha = sc.nextLine();

        while (!ehFim(senha)){
            if(validacao(senha)){
                System.out.println("SIM");
            } else {
                System.out.println("NAO");
            }

            senha = sc.nextLine();
        }
        sc.close();
    }
    
}
