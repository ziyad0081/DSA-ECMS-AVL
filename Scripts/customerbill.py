import matplotlib.pyplot as plt
import numpy as np
with open("Scripts/customer_bill.csv") as f:
    lines = [line for line in f]
    list_inj = [float(i) for i in lines[0].split(',')]
    list_con = [float(i) for i in lines[1].split(',')]
    list_avg = [float(i) for i in lines[4].split(',')]
    day_start = lines[2]
    customer = lines[3]
    if(len(list_inj) > 30):
        dpi = 100
        fig_width = 5000 / dpi  # Width in inches
        fig_height = 800 / dpi  # Height in inches
        plt.figure(figsize=(fig_width,fig_height),dpi=dpi)
    
    plt.xticks(np.arange(0,len(list_con),step=1))
    plt.plot([float(i) for i in list_inj],'b', label='Injection')
    plt.plot([float(i) for i in list_con],'r',label='Consumption')
    plt.plot([float(i) for i in list_avg],'g',label='Average Temperatures')

    plt.xlabel('Days After '+day_start)
    plt.ylabel('Amount (Kw)')
    plt.title("Consumption and Injection for "+customer)
    plt.legend()
    plt.show()

