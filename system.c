#include <stdio.h> 
#include <conio.h>  
#include <string.h>
#include <time.h>

typedef struct {
  int codigo;
  char nome[50];
  char modelo[50];
  int quantidade;
  float preco;
  int quantidadeVendida;
}
celular;

typedef struct {
  int codigoCelular;
  char codigoCliente[11];
  float totalVenda;
  char dataVenda[11];
}
venda;

typedef struct {
  char nome[50];
  char cpf[11];
  char endereco;
}
cliente;

int gerarCodigoCelular(celular estoque[], int qtdCelulares) {
  int maiorCodigo = 0;
  for (int i = 0; i < qtdCelulares; i++) {
    if (estoque[i].codigo > maiorCodigo) {
      maiorCodigo = estoque[i].codigo;
    }
  }
  return maiorCodigo + 1;
}

int buscarCliente(cliente clientes[], int qtdClientes, char cpf[]) {
    if(qtdClientes <= 0){
        printf("Lista de clientes vazia!\n");
        return -1;
    }
    if(cpf == NULL || strlen(cpf) == 0){
        printf("CPF inválido!\n");
        return -1;
    }
    for (int i = 0; i < qtdClientes; i++) {
        if (strcmp(clientes[i].cpf, cpf) == 0) {
            return i;
        }
    }
    printf("CPF passado como parametro: %s\n", cpf);
    for (int i = 0; i < qtdClientes; i++) {
    printf("CPF na estrutura cliente: %s\n", clientes[i].cpf);
    if (strcmp(clientes[i].cpf, cpf) == 0) {
        return i;
    }
}

    return -1;
}

int buscarCelular(celular estoque[], int qtdCelulares, int codigo) {
  for (int i = 0; i < qtdCelulares; i++) {
    if (estoque[i].codigo == codigo) {
      return i;
    }
  }
  return -1;
}

int verificarCPFExistente(cliente clientes[], int qtdClientes, char cpf[]) {
  for (int i = 0; i < qtdClientes; i++) {
    if (strcmp(clientes[i].cpf, cpf) == 0) {
      return 1;
    }
  }
  return 0;
}

void salvarEstoque(celular estoque[], int qtdCelulares) {
  FILE * arquivo = fopen("estoque.dat", "wb");
  if (arquivo == NULL) {
    printf("Erro ao abrir arquivo!\n");
    return;
  }
  fwrite(estoque, sizeof(celular), qtdCelulares, arquivo);
  fclose(arquivo);
}

void carregarEstoque(celular estoque[], int * qtdCelulares) {
  FILE * arquivo = fopen("estoque.dat", "rb");
  if (arquivo == NULL) {
    printf("Erro ao abrir arquivo!\n");
    return;
  }
  *qtdCelulares = fread(estoque, sizeof(celular), 100, arquivo);
  
  if(*qtdCelulares < 0)
  {
    printf("Erro ao carregar estoque\n");
    return;
  }
  
  if(*qtdCelulares < 0)
  {
    printf("Estoque carregado com menos itens que o esperado\n");
  }
  fclose(arquivo);
}


void salvarClientes(cliente clientes[], int qtdClientes) {
  FILE * arquivo = fopen("clientes.dat", "wb");
  if (arquivo == NULL) {
    printf("Erro ao abrir arquivo!\n");
    return;
  }
  if (qtdClientes <= 0) {
    printf("Nenhum cliente para salvar!\n");
    return;
  }
  fwrite(clientes, sizeof(cliente), qtdClientes, arquivo);
  fclose(arquivo);
}

void carregarClientes(cliente* clientes, int* qtdClientes){
    FILE* arquivo = fopen("clientes.dat", "rb");
    if(arquivo == NULL){
        printf("Erro ao abrir arquivo!\n");
        return;
    }
    *qtdClientes = fread(clientes, sizeof(cliente), 100, arquivo);
    if(*qtdClientes < 0){
        printf("Erro ao carregar clientes!\n");
        return;
    }
    if(*qtdClientes < 0){
        printf("Quantidade de clientes carregados diferente do esperado!\n");
    }
    fclose(arquivo);
}


void cadastrarCelular(celular estoque[], int * qtdCelulares) {
  printf("Nome: ");
  scanf("%s", estoque[ * qtdCelulares].nome);
  printf("Modelo: ");
  scanf("%s", estoque[ * qtdCelulares].modelo);
  printf("Quantidade: ");
  scanf("%d", & estoque[ * qtdCelulares].quantidade);
  printf("Preco: ");
  scanf("%f", & estoque[ * qtdCelulares].preco);
  estoque[ * qtdCelulares].codigo = gerarCodigoCelular(estoque, * qtdCelulares);
  ( * qtdCelulares) ++;
  salvarEstoque(estoque, * qtdCelulares);
}

void cadastrarCliente(cliente clientes[], int * qtdClientes) {
  printf("Nome: ");
  scanf("%s", clientes[ * qtdClientes].nome);
  printf("CPF: ");
  scanf("%s", clientes[ * qtdClientes].cpf);
  if (verificarCPFExistente(clientes, * qtdClientes, clientes[ * qtdClientes].cpf)) {
    printf("CPF já cadastrado!\n");
    return;
  }
  printf("Endereco: ");
  scanf("%s", clientes[ * qtdClientes].endereco);
  (*qtdClientes)++;
  salvarClientes(clientes, *qtdClientes);
}

void venderCelular(celular estoque[], int qtdCelulares, cliente clientes[], int qtdClientes, venda vendas[], int* qtdVendas) {
  char cpf[11];
  int codigoCelular, posicaoCelular, qtd;
  float total;
  printf("CPF do cliente: ");
  scanf("%s", cpf);
  int posicaoCliente = buscarCliente(clientes, qtdClientes, cpf);
  if (posicaoCliente == -1) {
    printf("Cliente não encontrado!\n");
    return;
  }
  printf("Celulares disponíveis no estoque:\n");
  for (int i = 0; i < qtdCelulares; i++) {
    if (estoque[i].quantidade > 0) {
      printf("Codigo: %d, Nome: %s, Modelo: %s, Preco: %.2f\n", estoque[i].codigo, estoque[i].nome, estoque[i].modelo, estoque[i].preco);
    }
  }
  printf("Informe o codigo do celular desejado: ");
    scanf("%d", & codigoCelular);
  posicaoCelular = buscarCelular(estoque, qtdCelulares, codigoCelular);
  if (posicaoCelular == -1) {
    printf("Celular não encontrado!\n");
    return;
  }
  printf("Informe a quantidade desejada: ");
  scanf("%d", & qtd);
  if (qtd > estoque[posicaoCelular].quantidade) {
    printf("Quantidade indisponível no estoque!\n");
    return;
  }
  estoque[posicaoCelular].quantidade -= qtd;
  total = qtd * estoque[posicaoCelular].preco;
  printf("Total da venda: R$ %.2f\n", total);
  vendas[*qtdVendas].codigoCelular = codigoCelular;
  strcpy(vendas[*qtdVendas].codigoCliente, cpf);
  vendas[*qtdVendas].totalVenda = total;
  estoque[posicaoCelular].quantidadeVendida += qtd;
  (*qtdVendas)++;
  salvarEstoque(estoque, qtdCelulares);
}



void consultarEstoque(celular estoque[], int qtdCelulares) {
  printf("Celulares disponíveis no estoque:\n");
  for (int i = 0; i < qtdCelulares; i++) {
    if (estoque[i].quantidade > 0) {
      printf("Codigo: %d, Nome: %s, Modelo: %s, Preco: %.2f, Quantidade: %d\n", estoque[i].codigo, estoque[i].nome, estoque[i].modelo, estoque[i].preco, estoque[i].quantidade);
    }
  }
}

void celularMaisVendido(celular estoque[], int qtdCelulares) {
  int indice = 0;
  int maiorVenda = estoque[0].quantidadeVendida;
  for (int i = 1; i < qtdCelulares; i++) {
    if (estoque[i].quantidadeVendida > maiorVenda) {
      maiorVenda = estoque[i].quantidadeVendida;
      indice = i;
    }
  }
  printf("Celular mais vendido: Codigo: %d, Nome: %s, Modelo: %s, Quantidade Vendida: %d\n", estoque[indice].codigo, estoque[indice].nome, estoque[indice].modelo, estoque[indice].quantidadeVendida);
}

void historicoCliente(cliente clientes[], int qtdClientes, venda vendas[], int qtdVendas) {
  char cpf[11];
  printf("Informe o CPF do cliente: ");
  scanf("%s", cpf);
  int posicaoCliente = buscarCliente(clientes, qtdClientes, cpf);
  if (posicaoCliente == -1) {
    printf("Cliente não encontrado!\n");
    return;
  }
  printf("Histórico de compras do cliente %s:\n", clientes[posicaoCliente].nome);
  for (int i = 0; i < qtdVendas; i++) {
    if (strcmp(vendas[i].codigoCliente, cpf) == 0) {
      printf("Codigo do celular: %d, Total da venda: R$%.2f, Data: %s\n", vendas[i].codigoCelular, vendas[i].totalVenda, vendas[i].dataVenda);
    }
  }
}

int main() {
  celular estoque[100];
  cliente clientes[100];
  venda vendas[100];
  int opcao, qtdCelulares = 0, qtdClientes = 0, qtdVendas = 0;
  carregarEstoque(estoque, & qtdCelulares);
  carregarClientes(clientes, & qtdClientes);
  do {
    printf("\nMenu:\n1 - Vender Celular\n2 - Celulares no estoque\n3 - Celular mais vendido\n4 - Histórico de um cliente\n5 - Cadastrar Cliente\n6 - Cadastrar Celular\n0 - Sair\nOpção: ");
    scanf("%d", & opcao);
    switch (opcao) {
    case 1:
      venderCelular(estoque, qtdCelulares, clientes, qtdClientes, vendas, & qtdVendas);
      break;
    case 2:
      consultarEstoque(estoque, qtdCelulares);
      break;
    case 3:
      celularMaisVendido(estoque, qtdCelulares);
      break;
    case 4:
      historicoCliente(clientes, qtdClientes, vendas, qtdVendas);
      break;
    case 5:
      cadastrarCliente(clientes, & qtdClientes);
      break;
    case 6:
      cadastrarCelular(estoque, & qtdCelulares);
      break;
    }
  } while (opcao != 0);
  return 0;
}