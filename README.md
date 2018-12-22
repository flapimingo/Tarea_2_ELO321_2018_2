# Homework_2_ELO321_2018_2

The following project consists of use and application of pipes to communicate two child process, reading and sending messages to each other.

## Getting Started

These instructions will get you a copy of the project up and running on your local machine for development and testing purposes. 

### Prerequisites

What things you need to install the software. 

```
* Intel C ccompiler >= 4.7.2 
```

### Installing

How to install them.

Install gcc in Debian or Ubuntu.
```
sudo apt-get install gcc
```
## Running the tests

For run project you should use makefile or you can compilate files with gcc.

### Compilate Files whit Makefile

First you run Makefile.

```
make 
make clean 
```
then, the program is compiled.

### Run the compiled with Makefile
```
./Tarea
```
Inside the file named output.txt, you should see how the process communicate.
Example:

```
cat output.txt
message sended: Hi!
send queue status: 4 messages left
message recept: Hi!
recept queue status: 1 message in queue
```

### Compilate and Run Files whit gcc

First you must open folder of PartX (X is letter of Stage). 
```
cd PartX
```

Then you compilate as folowing:
```
gcc *.c *.h -o Tarea
```
Obs: * *.c and *.h are all the files used to create the code of the program*

Then run the Program
```
./Tarea
```

## Built With

* [gcc](https://gcc.gnu.org/onlinedocs/) - The web gcc
* [Makefile](https://www.gnu.org/software/make/manual/html_node/Simple-Makefile.html) - Reference of good practices of makefile in GNU linux


## Authors

* **Cristian Bruna** - *Student* - telematic engineering student - 201630019-8 - cristian.bruna@sansano.usm.cl
* **Pascal Arriagada** - *Student* - telematic engineering student - 201630006-6 - pascal.arriagada@sansano.usm.cl

## License

This project is licensed under GNU GPLv3 License - see the [LICENSE.md](LICENSE.md) file for details
