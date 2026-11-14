# kitBOOM

Programa em C que verifica se uma forma de embalar bombas em uma caixa de 6 cm x 6 cm é válida. O enunciado (Trabalho Prático I da disciplina de **Projeto e Análise de Algoritmos**, UFSJ, novembro de 2024) conta a história de uma empresa de explosivos que precisa embalar bombas em uma caixa, o "KitBOOM".

Trabalho desenvolvido em dupla.

## Autores

- Miguel de Assis Viveiros
- Nicolas Rafael Mendonça Teles

## O problema

- A caixa é uma grade de 6 x 6 células (tamanho fixo definido pelo enunciado) e deve ficar totalmente preenchida.
- As bombas têm 1 cm de largura e comprimento de 1 a 3 cm.
- Cada bomba tem uma de quatro cores (polaridades): Amarelo (`Am`), Verde (`Vd`), Vermelho (`Vm`) ou Azul (`Az`).
- Uma configuração só é válida se **nenhuma bomba encosta em outra da mesma cor**.

## Como funciona

1. O programa lê o **arquivo de composição**, que diz quais bombas existem, e soma suas áreas. A soma precisa ser exatamente 36, a área da caixa: como as bombas são voláteis, não pode sobrar espaço vazio, e é claro que todas precisam caber. Se a soma for menor, o programa avisa que está sobrando espaço; se for maior, avisa que as bombas não cabem. Nos dois casos ele encerra sem testar nenhuma configuração.
2. Depois lê o **arquivo de configuração**, que descreve uma ou mais maneiras de posicionar essas bombas. Para cada configuração, as bombas são colocadas em uma matriz 6 x 6 de cores, e o programa verifica se há bombas adjacentes de mesma cor.
3. Para cada configuração, imprime no terminal se ela é **válida** ou **inválida**.

## Compilar e executar

Requisitos: `gcc` e `make`, em Linux.

```
make compile
./main -k composicao.txt -c configuracao.txt
```

| Opção | Significado |
|---|---|
| `-k` | arquivo de composição |
| `-c` | arquivo de configuração |
| `-n` | (opcional) repete o teste do arquivo de configuração N vezes, para aumentar artificialmente a entrada ao medir o tempo de execução |

Ao final, o programa mostra o tempo de processador, o tempo real e a memória máxima usada.

## Formato dos arquivos

**Composição:** uma linha por tipo de bomba, no formato `quantidade tamanho+cor`. Exemplo (`composicao2.txt`: 3 bombas de tamanho 3 de cada uma das quatro cores, 12 bombas no total, área 36):

```
3 3Az
3 3Vm
3 3Vd
3 3Am
```

**Configuração:** uma linha por bomba, no formato `linha-inicial coluna-inicial linha-final coluna-final tamanho+cor`. Configurações diferentes ficam separadas por uma linha em branco. Exemplo (primeiras linhas de uma configuração; `1 1 3 1 3Az` é uma bomba azul de tamanho 3, da linha 1 à linha 3, na coluna 1):

```
1 1 3 1 3Az
4 1 6 1 3Vm
1 2 3 2 3Vd
...
```

## Saída

Exemplo com os arquivos `composicao2.txt` e `configuracao2.txt`:

```
Composição correta, agora testaremos a configuração
A configuração número 1 é válida!
A configuração número 2 é inválida!
A configuração número 3 é inválida!
```

## Arquivos

| Arquivo | Conteúdo |
|---|---|
| `main.c` | Argumentos, laço principal e medição de tempo |
| `logica.c` | Criação das bombas e do kit, posicionamento na matriz e teste de adjacência |
| `entradaSaida.c` | Leitura dos arquivos de composição e de configuração |
| `prototipos.h` | Estruturas (`Cor`, `Bomba`, `Kit`) e declarações |
| `composicao*.txt`, `configuracao*.txt` | Dois casos de teste |
| `TP1_Documentação.pdf` | Documentação completa: rotinas, estruturas de dados, complexidade e análise dos tempos |
