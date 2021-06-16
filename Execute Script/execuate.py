import subprocess
import os
import csv
import numpy as np
from tqdm import tqdm
import time

output_file="./../Data/Linear_cost.csv"
programme="./../Code/Simulate"
cul_names=["Optimal of Male","Optimal of Female","Fitness of Male","Fitness of Female"]
if __name__=="__main__":
    file=open(output_file,"w+") #If not exist create one
    csv_module=csv.DictWriter(file,fieldnames=cul_names)
    csv_module.writeheader()
    pbar=tqdm(total=16000)
    for male_sf in range(-10,10):
        for male_k in list(set(np.arange(0.1,1,0.1) + range(1,10))):
            for female_sf in range(-10, 10):
                for female_k in list(set(np.arange(0.1, 1, 0.1) + range(1, 10))):
                    return_stream=subprocess.check_output([programme,str(male_sf),str(male_k),str(female_sf),str(female_k)])
                    returntext=return_stream.decode('utf-8')
                    returndata=returntext.split(',')
                    dia={cul_names[i]:returndata[i] for i in range(len(cul_names))}
                    csv_module.writerow(dia)
                    pbar.update(1)
    pbar.close()


