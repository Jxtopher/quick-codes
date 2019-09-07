#!/usr/bin/env python
# -*- coding=utf-8 -*-

#******************************************************************************
# File : managerRun.py
#
# Author : Jxtopher
# Date create : Mon Jul 27 00:48:01 2015
# Description : Execution de programme en parallel
#******************************************************************************


from multiprocessing import Pool

import sys
import time
import numpy

if (sys.version_info > (3, 0)):
	# Python 3 code in this block
	import subprocess
else:
	# Python 2 code in this block
	from commands import getstatusoutput

# run_function	la fonction a executer
# cmds_exec	list des args de la fonction
# nbProcessus	Nombre de processus a utiliser
# stdout	"" -> sortie stdout | "data.log" fichier de sortie
# ret		False -> recupere pas les sorties de la fonction worker
def parallelExecution(run_function, cmds_exec, nbProcessus = 1, stdout = None, ret = False):
	def secondsToStr(t):
	    return "%d:%02d:%02d.%03d" % \
		reduce(lambda ll,b : divmod(ll[0],b) + ll[1:],
		    [(t*1000,),1000,60,60])

	if stdout != "" and stdout != None:
		sys.stdout = open(stdout, 'a')

	startTime = time.time()
	jobs = []
	retInfo = []
	pool = Pool(processes = nbProcessus)
	
	numpy.random.seed = 0
	numpy.random.shuffle(cmds_exec)

	#print("[+] Nomber of execution " + str(len(cmds_exec)))
	#print("[+] " + str(cmds_exec[0]))

	try:
		if ret:
			jobs = pool.map_async(run_function, cmds_exec)
			pool.close()
			#pool.join()
			retInfo = jobs.get()
		else:
			pool.map_async(run_function, cmds_exec)
			pool.close()
			#pool.join()
	except KeyboardInterrupt:
		print('parent received control-c')
		pool.terminate()

	#print("[+] Execution time " + secondsToStr(time.time() - startTime))
	if stdout != None:
		if stdout != "":
			if retInfo != []:
				print(retInfo)
			sys.stdout = sys.__stdout__
	return retInfo

# function worker execute des prgrammes exterieurs avec des
# parametres command_line
def worker(command_line):
	try:
		if (sys.version_info > (3, 0)):
			# Python 3 code in this block
			return subprocess.getstatusoutput(command_line)
		else:
			# Python 2 code in this block
			return getstatusoutput(command_line)
 		
	except KeyboardInterrupt:
 		return 'KeyboardException'
 
# # myfunction est une fonction qui prend un parametre list
# # et retourne un resultat
# def myfunction(list_param):
# 	a = list_param[0]
# 	b = list_param[1]
# 	return a + b
# 
# if __name__ == "__main__":
# 
# 	print("Exemple 1 : ")
# 	cmds_exec = ["./a.out 90000"] * 500
# 	print(parallelExecution(worker, cmds_exec, 6, "", True))
# 
# 
# 	print("Exemple 2 : ")
# 	list_param = [[4, 5], [4, 10]]
# 	print(parallelExecution(myfunction, list_param, 6, "XX", True))
