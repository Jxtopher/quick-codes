///
/// \file fork.cpp
/// \author Jxtopher
/// \version 1 bêta
/// \date 27 Jan 2019
/// \brief *
///

#ifndef LAUNCHERFORK_H
#define LAUNCHERFORK_H

#include <string>
#include <cstring>
#include <cstdio>
#include <sys/wait.h>
#include <unistd.h>
#include <cstdlib>
#include <stdarg.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <poll.h>

#ifdef DEBUG
#define DEBUG_TRACE(msg) std::cerr<<"[+] "<<__FILE__<<":"<<__LINE__<<" "<<msg<<std::endl;	
#define DEBUG_VAR(variable) std::cerr<<"[+] "<<__FILE__<<":"<<__LINE__<<" "<<#variable << " = " << (variable) << std::endl;
#else
#define	DEBUG_TRACE(msg) 
#define DEBUG_VAR(variable)
#endif


#define PARENT_READ read_pipe[0]
#define PARENT_WRITE write_pipe[1]
#define CHILD_WRITE read_pipe[1]
#define CHILD_READ  write_pipe[0]

using namespace std;

namespace jxtopher {
class Fork  {
	public:
		Fork(string _subExecName) :
			subExecName(_subExecName) {

			if(access(subExecName.c_str(), F_OK ))
				throw string("[-] File \"")+ string(subExecName.c_str()) +string("\" does not exist");
		
			// Creation argv
			argv = new char*[1];
			argv[0] = new char[subExecName.size()];
			strncpy(argv[0], subExecName.c_str(), subExecName.size());

			// Creation envp
			envp = NULL;
		}

		Fork(string _subExecName, unsigned int n_args, ...) :
			subExecName(_subExecName) {
			
			if(access(subExecName.c_str(), F_OK ))
				throw string("[-] File \"")+ string(subExecName.c_str()) +string("\" does not exist");

			// Creation argv
			argv = new char*[n_args+1];
			argv[0] = new char[subExecName.size()];
			strncpy(argv[0], subExecName.c_str(), subExecName.size());

			string val;
			
			va_list vl;
			va_start(vl, n_args);

			for (unsigned int i = 0 ; i < n_args ; i++) {
				val=va_arg(vl,char *);
				argv[i+1] = new char[val.size()];
				strncpy(argv[i+1], val.c_str(), val.size());
			}
			va_end(vl);

			// Creation envp
			envp = NULL;
		}

		/*Fork(string _subExecName, int argc, const char **_argv, const char **_envp) {
			// Creation argv
		}*/

		void run() {
			// Create the pipe
			if (pipe(read_pipe) == -1)
				throw string("[-] Pipe failed");

			if (pipe(write_pipe) == -1)
				throw string("[-] Pipe failed");
			
			cpid = fork();

			switch (cpid) {
				case -1 :
					perror("fork");
					throw string("[-] Fork breaking");
				case 0 : // le fils
					DEBUG_TRACE("Processus fils")
					close(PARENT_READ);
					close(PARENT_WRITE);

					dup2(CHILD_READ, STDIN_FILENO);
					dup2(CHILD_WRITE, STDOUT_FILENO);
					close(CHILD_READ);
					close(CHILD_WRITE);
					
					
					// execute the process
					//execvpe(argv[0], argv, _envp);
					execvp(argv[0], argv);
					
					exit(2);
				default : // le pere
					//if (fcntl(PARENT_READ, F_SETFL, O_NONBLOCK) < 0) 
        			//	exit(2);
					close(CHILD_READ);
					close(CHILD_WRITE);
					
					DEBUG_TRACE("Pere: a cree processus")
					DEBUG_VAR(cpid)
			}
		}

		virtual ~Fork() {
			kill(cpid,SIGUSR1);
			do {
				if (waitpid(cpid, &status, WUNTRACED | WCONTINUED) == -1) {
					perror("waitpid");
					exit(EXIT_FAILURE);
				}

				if (WIFEXITED(status))
					cout<<"Terminé, code="<<WEXITSTATUS(status)<<endl;
				else if (WIFSIGNALED(status))
					cout<<"Tué par le signal "<<WTERMSIG(status)<<endl;
				else if (WIFSTOPPED(status))
					cout<<"Arrêté par le signal "<<WSTOPSIG(status)<<endl;
				else if (WIFCONTINUED(status))
					cout<<"Relancé"<<endl;
				
			} while (!WIFEXITED(status) && !WIFSIGNALED(status));
		}

        void send(string msg) {
			char *buff = new char[msg.size()];
			for(unsigned int i = 0 ; i < msg.size() ; i++) {
				buff[i] = msg[i];
				printf("%x ", buff[i]);
			}

            if(write(PARENT_WRITE,  buff, sizeof(char) * msg.size()) == -1)
				cerr<<"pipe failed\n"<<endl;
        }

		/* src:https://stackoverflow.com/questions/13811614/how-to-see-if-a-pipe-is-empty
		bool canReadFromPipe(int fd){
			//file descriptor struct to check if POLLIN bit will be set
			//fd is the file descriptor of the pipe
			struct pollfd fds{ .fd = fd, .events = POLLIN };
			//poll with no wait time
			int res = poll(&fds, 1, 0);

			//if res < 0 then an error occurred with poll
			//POLLERR is set for some other errors
			//POLLNVAL is set if the pipe is closed
			if(res < 0||fds.revents&(POLLERR|POLLNVAL))
			{
				//an error occurred, check errno
			}

			return fds.revents&POLLIN;
		}*/

        string recv() {
			int size_buff = 20;
			char *buff = new char[size_buff];
			int return_size = -1;
			
			char *ret_string = new char[0];
			int size_ret_string = 0;

			int critere;

			do {
            	return_size = read(PARENT_READ, buff, sizeof(char) * size_buff);
				critere = errno;
				
				if ( 0 < return_size) {
					ret_string = (char *) realloc (ret_string, size_ret_string + return_size * sizeof(char));
					size_ret_string += return_size * sizeof(char);

					char * x = ret_string + (size_ret_string - return_size);
				
					strncpy(x  , buff, return_size);
				}

				switch (critere) {
					case EAGAIN :
						cout<<"EAGAIN"<<endl;
						break;
					case EBADF :
						cout<<"EBADF"<<endl;
						break;
					case EFAULT :
						cout<<"EFAULT"<<endl;
						break;
					case EINTR :
						cout<<"EINTR"<<endl;
						break;
					case EINVAL :
						cout<<"EINVAL"<<endl;
						break;
					case EIO :
						cout<<"EIO"<<endl;
						break;
					case EISDIR :
						cout<<"EISDIR"<<endl;
						break;
					default:
						break;
				}
			} while(return_size == size_buff);

			/*==================
			do {
				
            	return_size = read(PARENT_READ, buff, sizeof(char) * size_buff);
				cout<<__FILE__<<" : "<<__LINE__<<" return_size="<<return_size<<endl;
				if ( 0 < return_size) {
					ret_string = (char *) realloc (ret_string, size_ret_string + return_size * sizeof(char));
					size_ret_string += return_size * sizeof(char);

					char * x = ret_string + (size_ret_string - return_size);
				
					strncpy(x  , buff, return_size);
				}
			} while(return_size == size_buff);
			*/

			/*ret_string = (char *) realloc (ret_string, size_ret_string + 2 * sizeof(char));
			size_ret_string += 1 * sizeof(char);

			ret_string[size_ret_string - 1] = '\0';*/

			/*cout<<"++++++++++++++"<<endl;
			cout<<ret_string<<endl;
			cout<<"++++++++++++++"<<endl;
			for (int i = 0 ; i < size_ret_string ; i++) {
				printf("%x %c | ", ret_string[i], ret_string[i]);
			}
			cout<<"++++++++++++++"<<endl;*/

			string x;
			
			for (int i = 0 ; i < size_ret_string ; i++) {
				x += ret_string[i];
			}

			delete buff;
			delete ret_string;
			
			return x;
        }

		protected:
			string subExecName;	// Name of the program to execute
			char ** argv;		// Arguments
			char ** envp;

			int status;
			pid_t cpid;
			int read_pipe[2];
			int write_pipe[2];

};

class UnitTest_Fork {
	public:
	UnitTest_Fork() {

	}
	virtual ~UnitTest_Fork() {

	}

	void run() {
		callBash();
		callls();
	}

	int callBash() {
		try {
			Fork f("/bin/bash");
			f.run();

			f.send("/bin/ls /etc\n");
			cout<<"$ /bin/ls /etc ======="<<endl;
			cout<<f.recv()<<endl;

			cout<<"$ /bin/ls /dev ======="<<endl;
			f.send("/bin/ls /dev\n");
			cout<<f.recv()<<endl;

			cout<<"$ /usr/bin/xxd /etc/passwd / ======="<<endl;
			f.send("/usr/bin/xxd /etc/passwd\n");
			cout<<f.recv()<<endl;
		}
		catch(string &msg) {
			cerr<<msg<<endl;
			return EXIT_FAILURE;
		}
		return EXIT_SUCCESS;
	}

	int callls() {
		try {
			Fork f("/bin/ls", 1, ".");
			f.run();
			cout<<"RECV ======="<<endl;
			cout<<f.recv()<<endl;
		}
		catch(string &msg) {
			cerr<<msg<<endl;
			return EXIT_FAILURE;
		}
		return EXIT_SUCCESS;
	}
	protected:
};

}

#endif
