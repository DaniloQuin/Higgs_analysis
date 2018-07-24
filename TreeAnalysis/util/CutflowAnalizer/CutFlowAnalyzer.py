#!/usr/bin/env python
import csv
import sys



thread = 7
num_file = 13
file_min = 6
num_cut = 19

if __name__ == '__main__':
	result = [[[] for j in range(num_cut)] for i in range(num_file)]
	for j in range(file_min,file_min+num_file):
		for i in range(thread):
			if j!= 16:
				with open(sys.argv[1] + str(j)+ ".dat" + str(i) ,'r') as archivo:
					reader = csv.reader(archivo,delimiter=",")
					cut = 0
					for row in reader:
						result[j-file_min][cut].append(row[1])
						cut += 1
	with open("cutflow_output.csv",'w') as salida:
		escritor = csv.writer(salida,delimiter=",")
		for archivo in range(num_file):
			for corte in range(num_cut):
				temp = [archivo,corte]
				temp.extend(result[archivo][corte])
				
				escritor.writerow(temp)
