import subprocess
import os
import csv
import numpy as np
from tqdm import tqdm
import time
sf=[-10,-8,-6,-4,-2,0,2,4,6,8,10]
k=[0,0.2,0.4,0.6,0.8,1,2,4,6,8,10]
output_file="./../Data/Linear_cost.csv"
programme="./../Code/Simulate"
cul_names=["Parameter","Optimal of Male","Optimal of Female","Fitness of Male","Fitness of Female"]
if __name__=="__main__":
    file=open(output_file,"w+") #If not exist create one
    csv_module=csv.DictWriter(file,fieldnames=cul_names)
    csv_module.writeheader()
    pbar=tqdm(total=14641,position=0,desc="Total")
    pbar_male_sf = tqdm(total=11, position=1, desc="Male_Sf")
    pbar_male_k = tqdm(total=11, position=2, desc="Male_k")
    pbar_female_sf = tqdm(total=11, position=3, desc="Female_sf")
    pbar_female_k = tqdm(total=11, position=4, desc="Female_k")
    for male_sf in sf:
        pbar_male_sf.update(1)
        for male_k in k:
            pbar_male_k.update(1)
            for female_sf in sf:
                pbar_female_sf.update(1)
                for female_k in k:
                    pbar_female_k.update(1)
                    return_stream=subprocess.check_output([programme,str(male_sf),str(male_k),str(female_sf),str(female_k)])
                    returntext=return_stream.decode('utf-8')
                    returndata=returntext.split(',')
                    returndata.insert(0,'({},{},{},{})'.format(male_sf,male_k,female_sf,female_k))
                    dia={cul_names[i]:returndata[i] for i in range(len(returndata))}
                    #dia["Parameter"]='({},{},{},{})'.format(male_sf,male_k,female_sf,female_k)
                    csv_module.writerow(dia)
                    pbar.update(1)
                pbar_female_k.reset()
            pbar_female_sf.reset()
        pbar_male_k.reset()
    pbar_male_sf.reset()
    pbar.close()
    pbar_male_sf.close()
    pbar_male_k.close()
    pbar_female_sf.close()
    pbar_female_k.close()


