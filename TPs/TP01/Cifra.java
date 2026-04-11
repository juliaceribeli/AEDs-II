
public class Cifra{

    public static boolean isFim(String s){
        return (s.length() == 3 && s.charAt(0) == 'F' && s.charAt(1) == 'I' && s.charAt(2) == 'M');
    }
    public static void main(String[] args){

        String frase = MyIO.readLine();

        while (!isFim(frase)){

            String codificada = "";

            for (int i = 0; i < frase.length(); i++){
                char letra = frase.charAt(i);
                codificada += (char)(letra + 3);
            }

            MyIO.println(codificada);

            frase = MyIO.readLine();
        }
    }
}