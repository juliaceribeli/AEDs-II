import java.util.*;
import java.io.*;

class Data {
    private int ano;
    private int mes;
    private int dia;

    public Data(){
        this.ano = 0;
        this.mes = 0;
        this.dia = 0;
    }

    public int getAno(){
        return this.ano;
    }
    public void setAno(int ano){
        this.ano = ano;
    }
            
    public int getMes(){
        return this.mes;
    }
    public void setMes(int mes){
        this.mes = mes;
    }

    public int getDia(){
        return this.dia;
    }
    public void setDia(int dia){
        this.dia = dia;
    }

    public static Data parseData(String s){
        Data d = new Data();
    
        int num = 0;
        int etapa = 0;
    
        for (int i = 0; i < s.length(); i++){
            char c = s.charAt(i);
            if (c == '-'){
                if (etapa == 0){     //ano
                    d.setAno(num);
                } else if (etapa == 1){     //mes
                    d.setMes(num);
                }  
                num = 0;
                etapa++;
            } else {
                int digito = c - '0';
                num = (num * 10) + digito;
            }
        }
    
        d.setDia(num);
    
        return d;    
    }

    public String formatar(){
        return String.format("%02d/%02d/%04d", this.dia, this.mes, this.ano);
    }
}
        
class Hora {
    private int hora;
    private int minuto;

    public Hora(){
        this.hora = 0;
        this.minuto = 0;
    }

    public int getHora(){
        return this.hora;
    }
    public void setHora(int hora){
        if (hora >= 0 && hora <= 23) {
            this.hora = hora;
        }
    }

    public int getMinuto(){
        return this.minuto;
    }
    public void setMinuto(int minuto){
        if (minuto >= 0 && minuto <= 59) {
            this.minuto = minuto;
        }
    }

    public static Hora parseHora(String s){
        Hora h = new Hora();

        int num = 0;

        for (int i = 0; i < s.length(); i++){
            char c = s.charAt(i);
            if(c == ':'){
                h.setHora(num);
                num = 0;
            } else {
                int digito = c - '0';
                num = (num * 10) + digito;
            }
        }
        h.setMinuto(num);
        
        return h;
    }

    public String formatar(){
        return String.format("%02d:%02d", this.hora, this.minuto);
    }
}

class Restaurante {
    private int id;
    private String nome;
    private String cidade;
    private int capacidade;
    private double avaliacao;
    private String[] tiposCozinha;
    private int faixaPreco;
    private Hora horarioAbertura;
    private Hora horarioFechamento;
    private Data dataAbertura;
    private boolean aberto;

    public Restaurante(){
        this.id = 0;
        this.nome = "";
        this.cidade = "";
        this.capacidade = 0;
        this.avaliacao = 0;
        this.tiposCozinha = new String[0];
        this.faixaPreco = 0;
        this.horarioAbertura = new Hora();
        this.horarioFechamento = new Hora();
        this.dataAbertura = new Data();
        this.aberto = false;        
    }

    public int getId(){
        return this.id;
    }
    public String getNome(){
        return this.nome;
    }
    public String getCidade(){
        return this.cidade;
    }
    public int getCapacidade(){
        return this.capacidade;
    }
    public double getAvaliacao(){
        return this.avaliacao;
    }
    public String[] getTiposCozinha(){
        return this.tiposCozinha;
    }
    public int getFaixaPreco(){
        return this.faixaPreco;
    }
    public Hora getHorarioAbertura(){
        return this.horarioAbertura;
    }
    public Hora getHorarioFechamento(){
        return this.horarioFechamento;
    }
    public Data getDataAbertura(){
        return this.dataAbertura;
    }
    public boolean getAberto(){
        return this.aberto;
    }


    public void setId(int id){
        this.id = id;
    }
    public void setNome(String nome){
        this.nome = nome;
    }
    public void setCidade(String cidade){
        this.cidade = cidade;
    }
    public void setCapacidade(int capacidade){
        this.capacidade = capacidade;
    }
    public void setAvaliacao(double avaliacao){
        this.avaliacao = avaliacao;
    }
    public void setTiposCozinha(String[] tiposCozinha){
        this.tiposCozinha = tiposCozinha;
    }
    public void setFaixaPreco(int faixaPreco){
        if (faixaPreco >= 1 && faixaPreco <= 4){
            this.faixaPreco = faixaPreco;
        }
    }
    public void setHorarioAbertura(Hora horarioAbertura){
        this.horarioAbertura = horarioAbertura;
    }
    public void setHorarioFechamento(Hora horarioFechamento){
        this.horarioFechamento = horarioFechamento;
    }
    public void setDataAbertura(Data dataAbertura){
        this.dataAbertura = dataAbertura;
    }
    public void setAberto(boolean aberto){
        this.aberto = aberto;
    }

    public static Restaurante parseRestaurante(String s){
        Restaurante r = new Restaurante();
        String parte = "";
        int coluna = 0; 
    
        for (int i = 0; i < s.length(); i++){
            char c = s.charAt(i);
            if (c == ','){
                if (coluna == 0){ //id
                    int num = 0;
                    for (int j = 0; j < parte.length(); j++){
                        char cr = parte.charAt(j);
                        num = (num * 10) + (cr - '0'); 
                    }
                    r.setId(num);
                } else if (coluna == 1){ //nome
                    r.setNome(parte);
                } else if (coluna == 2){ //cidade
                    r.setCidade(parte);
                } else if (coluna == 3){ //capacidade
                    int num = 0;
                    for (int j = 0; j < parte.length(); j++){
                        char cr = parte.charAt(j);
                        num = (num * 10) + (cr - '0'); 
                    }
                    r.setCapacidade(num);                    
                } else if (coluna == 4){ //avaliacao
                    double num = 0.0;
                    double divisor = 10.0;
                    boolean ponto = false;
                    for (int j = 0; j < parte.length(); j++){
                        char cr = parte.charAt(j);
                        if(cr == '.'){
                            ponto = true;
                        } else {
                            if (!ponto){
                                num = (num * 10) + (cr - '0');
                            } else {
                                num = num + ((cr - '0')/ divisor);
                                divisor *= 10;
                            }
                        }
                    }
                    
                    r.setAvaliacao(num);

                } else if (coluna == 5){ //tipos_cozinha

                    int tam = 1;
                    for (int j = 0; j < parte.length(); j++){
                        if(parte.charAt(j) == ';') tam++;
                    }

                    String[] cozinhas = new String[tam]; 

                    int cont = 0;
                    String tipo = "";

                    for (int j = 0; j < parte.length(); j++){
                        char cr = parte.charAt(j);

                        if (cr == ';'){
                            cozinhas[cont] = tipo;
                            cont++;
                            tipo = "";
                        } else {
                            tipo += cr;
                        }
                    }
                    cozinhas[cont] = tipo;

                    r.setTiposCozinha(cozinhas);
                } else if (coluna == 6){ //faixa_preco
                    int faixa = parte.length();
                    r.setFaixaPreco(faixa);
                } else if (coluna == 7){ //horario
                    Hora abertura = new Hora();
                    String hr = "";
                    for (int j = 0; j < parte.length(); j++){
                        char cr = parte.charAt(j);
                        
                        if(cr == '-'){
                            abertura = Hora.parseHora(hr);
                            hr = "";
                        } else {
                            hr += cr;
                        }
                    }
                    Hora fechamento = Hora.parseHora(hr);

                    r.setHorarioAbertura(abertura);
                    r.setHorarioFechamento(fechamento);
                } else if (coluna == 8){ //data_abertura
                    Data d = Data.parseData(parte);
                    r.setDataAbertura(d);
                } //fim if
                coluna++;
                parte = "";
            } else {
                parte += s.charAt(i);
            } // fim if ','
        } // fim for
        
        boolean aberto = false;

        if (parte.compareTo("true") == 0){
            aberto = true;
        }    
        
        r.setAberto(aberto);

        return r;
    }// fim parseRestaurante

    public String formatar(){
        // formatando os tipos de cozinha e faixa de preço antes de formar a string geral
        String cozinhasFormatadas = "[";
        for (int i = 0; i < this.tiposCozinha.length; i++){
            cozinhasFormatadas += tiposCozinha[i];
            if (i < tiposCozinha.length - 1) cozinhasFormatadas += ",";
        }
        cozinhasFormatadas += "]";

        String precoFormatado = "";
        for (int i = 0; i < this.faixaPreco; i++){
            precoFormatado += "$";
        }

        return String.format("[%d ## %s ## %s ## %d ## %s ## %s ## %s ## %s-%s ## %s ## %s]", 
                                        this.id,
                                        this.nome,
                                        this.cidade,
                                        this.capacidade,
                                        String.valueOf(this.avaliacao),
                                        cozinhasFormatadas,
                                        precoFormatado,
                                        this.horarioAbertura.formatar(),
                                        this.horarioFechamento.formatar(),
                                        this.dataAbertura.formatar(),
                                        this.aberto);
    }
}

class ColecaoRestaurantes {
    private int tamanho;
    private Restaurante[] restaurantes;

    public ColecaoRestaurantes() {
        this.tamanho = 0;
        this.restaurantes = new Restaurante[1000];
    }

    public int getTamanho(){
        return this.tamanho;
    }
    public Restaurante[] getRestaurantes(){
        return this.restaurantes;
    }

    public void lerCsv(String path){
        try {
        java.io.File arquivo = new java.io.File(path);
        java.util.Scanner leitor = new java.util.Scanner(arquivo);

        if (leitor.hasNextLine()) {
            leitor.nextLine();
        }

        while (leitor.hasNextLine()) {
            String linha = leitor.nextLine();
            
            Restaurante r = Restaurante.parseRestaurante(linha);
            
            this.restaurantes[this.tamanho] = r;
            this.tamanho++;
        }

        leitor.close();
    } catch (java.io.FileNotFoundException e) {
        System.out.println("Arquivo não encontrado!");
    }
    }

    public static ColecaoRestaurantes lerCsv() {
        ColecaoRestaurantes colecao = new ColecaoRestaurantes();
        colecao.lerCsv("/tmp/restaurantes.csv");
        return colecao;
    }


}



public class Eatery{

    public static void ordenarPorInsercao(Restaurante[] array, int n, int[] log) {
        for (int i = 1; i < n; i++) {
            Restaurante tmp = array[i];
            int j = i - 1;
            boolean inseriu = false;

            while (j >= 0 && !inseriu) {
                log[0]++;
                
                if (array[j].getCidade().compareTo(tmp.getCidade()) > 0) {
                    array[j + 1] = array[j];
                    log[1]++;
                    j--;
                } else {
                    inseriu = true; 
                }
            }
            array[j + 1] = tmp;
            log[1]++;
        }
    }

    public static boolean pesquisaSequencial(Restaurante[] array, int n, String nomeBuscado, int[] log) {
        boolean achou = false;
        int i = 0;

        while (i < n && !achou) {
            log[0]++;
            if (array[i].getNome().compareTo(nomeBuscado) == 0) {
                achou = true;
            }
            i++;
        }

        return achou;
    }
    public static void main(String[] args) {
        ColecaoRestaurantes colecao = ColecaoRestaurantes.lerCsv();
        Restaurante[] base = colecao.getRestaurantes();
        Restaurante[] arrayPesquisa = new Restaurante[1000];
        int nPesquisa = 0;
        
        Scanner sc = new Scanner(System.in);

        boolean lerEntrada = true;

        while(lerEntrada && sc.hasNextLine()){
            String linha = sc.nextLine();

            if(linha.compareTo("-1") == 0){
                lerEntrada = false;
            } else {
                //convertendo ID em int
                int idProcurado = 0;
                for(int i = 0; i < linha.length(); i++){
                    char c = linha.charAt(i);
                    if(c >= '0' && c <= '9'){
                        idProcurado = (idProcurado * 10) + (c - '0');
                    }
                }

                boolean achou = false;
                int indice = 0;
                while (!achou && indice < colecao.getTamanho()) {
                    if (base[indice].getId() == idProcurado) {
                        arrayPesquisa[nPesquisa] = base[indice];
                        nPesquisa++;
                        achou = true;
                    }
                    indice++;
                }
            }
        }

        int[] contadoresLog = new int[1];
        long inicioTempo = System.currentTimeMillis();

        boolean lendoNomes = true;
        while (lendoNomes && sc.hasNextLine()) {
            String nomeBuscado = sc.nextLine();

            nomeBuscado = nomeBuscado.replace("\r", "");

            if (nomeBuscado.compareTo("FIM") == 0) {
                lendoNomes = false;
            } else {
                boolean resultado = pesquisaSequencial(arrayPesquisa, nPesquisa, nomeBuscado, contadoresLog);
                
                if (resultado) {
                    System.out.println("SIM");
                } else {
                    System.out.println("NAO");
                }
            }
        }
        sc.close();

        long fimTempo = System.currentTimeMillis();
        long tempoTotal = fimTempo - inicioTempo;

        try {
            FileWriter arquivoLog = new FileWriter("896238_sequencial.txt");
            PrintWriter gravador = new PrintWriter(arquivoLog);
            gravador.printf("896238\t%d\t%d\n", contadoresLog[0], tempoTotal);
            gravador.close();
        } catch (IOException e) {
            System.out.println("Erro ao gravar log");
        }
    }
}