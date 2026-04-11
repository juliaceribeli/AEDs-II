import java.util.*;

public class Alteracao {

    public static boolean ehFim(String s){
        return (s.length() == 3 && s.charAt(0) == 'F' && s.charAt(1) == 'I' && s.charAt(2) == 'M');
    }
    public static void main (String [] args){
        Random gerador = new Random();
        gerador.setSeed(4);
        
        String frase = MyIO.readLine();

        while(!ehFim(frase)){
            char letra1 = ((char) ('a' + (Math.abs(gerador.nextInt()) % 26)));
            char letra2 = ((char) ('a' + (Math.abs(gerador.nextInt()) % 26)));
            String alterada = "";
    
            for (int i = 0; i < frase.length(); i++) {
                if (frase.charAt(i) == letra1){
                    alterada += letra2;
                } else {
                    alterada += frase.charAt(i);
                }
            }

            MyIO.println(alterada);

            frase = MyIO.readLine();
        }
    }
}
