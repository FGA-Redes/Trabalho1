# Trabalho1
Camada de Aplicação: Pingador/Resolvedor

# Alunos

- Laércio Silva	    130119105
- Vinícius Pinheiro 140066543

# Objetivo
1) Exercitar conceitos de programação de sistemas operacionais.
2) Estudar a implementação de esquemas de comunicações entre processos (IPC), especificamente
a utilização da interface socket.

# Ambiente de desenvolvimento:

SO: Debian Stretch
Compilador: gcc 6.3
Editor de texto: Atom
Codificação: UTF-8

# Limitações:
- Não existe validações para a entrada de argumentos
- Não existe comando de saída do programa

# Caso de teste:

1. Para compilar todo o projeto, digite make no diretório do exercício.
2. Execute o programa (./server) para executar o servidor.
3. Execute o programa (./client) com os parâmetros ip e comando para executar o o cliente.
3.1 Os parâmetros são _IP_ e _COMANDO_, sendo o IP da máquina na qual está rodando o server. O commando pode ser rsv e rtt. Quando o comando é rsv existe um terceiro parâmetro no qual deve se enviar o domínio.
