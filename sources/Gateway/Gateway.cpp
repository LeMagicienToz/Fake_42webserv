/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Gateway.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muteza <muteza@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 18:27:13 by mconreau          #+#    #+#             */
/*   Updated: 2024/06/21 16:42:44 by muteza           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Gateway.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muteza <muteza@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 18:27:13 by mconreau          #+#    #+#             */
/*   Updated: 2024/06/18 15:01:57 by muteza           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cstdlib> // For EXIT_FAILURE
#include <cstring> // For custom_strcpy
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <iostream>
#include <filesystem>
#include <vector>
#include "Gateway/Gateway.hpp"
#include "Http/Request.hpp"

Gateway::Gateway() {}

Gateway::Gateway(const Gateway &src) {
	*this = src;
}

Gateway::~Gateway() {}

Gateway& Gateway::operator=(const Gateway &rhs) {
	if (this != &rhs) {
		this->v = rhs.v;
	}
	return *this;
}

void Gateway::addenv(const std::string& key, const std::string& value) {
	std::string str = key + "=" + value;
	v.push_back(str);
}

char** Gateway::put_to_env() {
	char** envp = new char*[v.size() + 1];
	for (size_t i = 0; i < v.size(); ++i) {
		envp[i] = new char[v[i].size() + 1];
		String::custom_strcpy(envp[i], v[i].c_str());
	}
	envp[v.size()] = NULL; // Ensure the last element is NULL
	return envp;	
}

const char *Gateway::getAbsolutePathOfFile(const char *fileName) {
   static char absPath[PATH_MAX]; // PATH_MAX is defined in <limits.h>

    // Open the current directory
    DIR* dir = opendir(".");
    if (dir == NULL) {
        std::cerr << "Error in opendir: " << strerror(errno) << std::endl;
        return NULL;
    }

    // Read the directory entries
    struct dirent* entry;
    while ((entry = readdir(dir)) != NULL) {
        if (entry->d_type == DT_REG) { // Check if it's a regular file
            if (std::strcmp(entry->d_name, fileName) == 0) {
                std::strcpy(absPath, "./");
                std::strcat(absPath, entry->d_name);
                closedir(dir);
                return absPath;
            }
        }
    }

    // Close the directory
    closedir(dir);

    // File not found
    std::cerr << "File not found: " << fileName << std::endl;
    return NULL;
}

std::string Gateway::cgirun(Request& req) {
	int pipefd[2];
	if (pipe(pipefd) == -1) {
		perror("pipe");
		return ""; // Return empty string on error
	}

	pid_t pid = fork();
	if (pid == -1) {
		perror("fork");
		close(pipefd[0]);
		close(pipefd[1]);
		return ""; // Return empty string on error
	}

	if (pid == 0) {
		// Child process
		close(pipefd[0]); // Close reading end
		if (dup2(pipefd[1], STDOUT_FILENO) == -1) { // Redirect stdout to pipe
			perror("dup2");
			close(pipefd[1]);
			exit(EXIT_FAILURE);
		}
		close(pipefd[1]);

		addenv("QUERY_STRING", req.getHeader("user-agent",""));
		addenv("REQUEST_METHOD", req.getMethod());
		addenv("SERVER_PROTOCOL", req.getVersion());
		addenv("CONTENT_TYPE", req.getHeader("content-type",""));
		addenv("CONTENT_LENGTH", req.getHeader("content-length",""));
		addenv("HTTP_ACCEPT", req.getHeader("accept",""));
		addenv("SERVER_NAME", req.getHeader("host",""));
		addenv("HTTP_USER_AGENT", req.getHeader("user-agent",""));
		addenv("HTTP_ACCEPT_ENCODING", req.getHeader("accept-encoding",""));
		addenv("HTTP_ACCEPT_LANGUAGE", req.getHeader("accept-language",""));
		std::cout << req.getTarget() << std::endl;
		char** envp = put_to_env();

		std::cerr << "About to execute script..." << std::endl;

		std::vector<std::string> paths;
		// Absolute path to Script.py
		 const char* absPath = getAbsolutePathOfFile("Script.py");
   		if (absPath != NULL) 
	 	{
			char* const argv[] = { const_cast<char*>(absPath), NULL };
			if (execve(absPath, argv, envp) == -1) {
				perror("execve");
				std::cerr << "execve failed for: " << argv[0] << std::endl;
				std::cerr << "Path might be incorrect or file might not have execute permissions." << std::endl;
				std::cerr.flush();
			}
				exit(EXIT_FAILURE);
		}
	}
	else {
		// Parent process
		close(pipefd[1]); // Close writing end

		char buffer[1024];
		buffer[1023] = '\0';
		std::string response = "HTTP/1.1 200 OK\nContent-Type: text/html\n\n";
		ssize_t bytesRead;
		while ((bytesRead = read(pipefd[0], buffer, sizeof(buffer))) > 0) {
			response.append(buffer, bytesRead);
		}
		close(pipefd[0]);

		int status;
		waitpid(pid, &status, 0); // Wait for child process to finish
		if (WIFEXITED(status)) {
			std::cerr << "Child exited with status: " << WEXITSTATUS(status) << std::endl;
		} else if (WIFSIGNALED(status)) {
			std::cerr << "Child killed by signal: " << WTERMSIG(status) << std::endl;
		}
		return response;
	}
	return (NULL);
}
