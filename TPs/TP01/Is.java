public class Is {

    public static boolean ehFim(String s){
        return  (s.charAt(0) == 'F' && s.charAt(1) == 'I' && s.charAt(2) == 'M');
    }

    public static boolean ehVogal(String s){
        String result = s.toLowerCase();
        boolean vogal = true;
        for (int i = 0; i < result.length(); i++) {
            if (result.charAt(i) != 'a' && result.charAt(i) != 'e' && result.charAt(i) != 'i' && result.charAt(i) != 'o' && result.charAt(i) != 'u'){
                vogal = false;
            }
        }
        return vogal;
    }

    public static boolean ehConsoante(String s){
        String result = s.toLowerCase();
        boolean consoante = true;
        for (int i = 0; i < result.length(); i++){
            if (!(result.charAt(i) >= 'a' && result.charAt(i) <= 'z') || result.charAt(i) == 'a' || result.charAt(i) == 'e' || result.charAt(i) == 'i' || result.charAt(i) == 'o' || result.charAt(i) == 'u'){
                consoante = false;
            }
        }
        return consoante;
    }

    public static boolean ehInt(String s){
        boolean inteiro = true;

        for (int i = 0; i < s.length(); i++) {
            if(s.charAt(i) == '.' || s.charAt(i) == ',' || (s.charAt(i) >= 'A' && s.charAt(i) <= 'z')){
                inteiro = false;
            }
        }

        return inteiro;
    }

    public static boolean ehFloat(String s){
        boolean real = true;
        int qtdponto = 0;

        for (int i = 0; i < s.length(); i++) {
            if (s.charAt(i) >= 'A' && s.charAt(i) <= 'z'){
                real = false;
                i = s.length();
            } else if (s.charAt(i) == '.' || s.charAt(i) == ','){
                qtdponto++;
                if (qtdponto > 1 || qtdponto == 0){
                    real = false;
                }
            }
        }

        return real;
    }

    public static void main(String[] args){
        
        String s = MyIO.readLine();
        while (!ehFim(s)){
     
            if(ehVogal(s) == true) {
                MyIO.print("SIM ");
            } else {
                MyIO.print("NAO ");
            }
            if(ehConsoante(s) == true) {
                MyIO.print("SIM ");
            } else {
                MyIO.print("NAO ");
            }
            if(ehInt(s) == true) {
                MyIO.print("SIM ");
            } else {
                MyIO.print("NAO ");
            }
            if(ehFloat(s) == true) {
                MyIO.print("SIM\n");
            } else {
                MyIO.print("NAO\n");
            }

            s = MyIO.readLine();
        }
    }
}
