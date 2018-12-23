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
make run
make clean 
```
then, the program is compiled.

### Run the compiled with Makefile

We recommend to run it manually, sometimes it seems to dont write in the file *Troubles at the end*

```
./Tarea > comm_log_file.txt
```
Inside the file named comm_log_file.txt, you should see how the process communicate.
Example:

```
cat comm_log_file.txt
message sended: Va!
send queue status: 4 messages left
message recept: Va!
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

## Troubles

Some times dont write the comm_log_file.txt properly. Maybe by a bad way to write the output file.

The communnication between two child process can be done in many ways, one of them is by using pipes, generally we can set one pipe to each direction and close the other one that's not in use. In this case, we tried using only one pipe and made it bidirectional.
Our program is not completed, because we couldn't figure how to synchronize both process, so it hangs up sometimes.
When it works as it has to, the process send messages to each other, and put it in a recept queue.
Maybe implementing semaphores or producer/consumer solution could help, in a future, to fix this issue and to let it functional. 
Anyway, the recommended way is to always use pipes unidirectionally.


## Built With

* [gcc](https://gcc.gnu.org/onlinedocs/) - The web gcc
* [Makefile](https://www.gnu.org/software/make/manual/html_node/Simple-Makefile.html) - Reference of good practices of makefile in GNU linux


## Authors

* **Cristian Bruna** - *Student* - telematic engineering student - 201630019-8 - cristian.bruna@sansano.usm.cl
* **Pascal Arriagada** - *Student* - telematic engineering student - 201630006-6 - pascal.arriagada@sansano.usm.cl

## License

This project is licensed under GNU GPLv3 License - see the [LICENSE.md](LICENSE.md) file for details
