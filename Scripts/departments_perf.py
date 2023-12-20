import matplotlib.pyplot as plt


with open("Scripts/department_perf.csv") as f:
    lines = [line for line in f]
    list_profit = [float(i)/10000 for i in lines[0].split(',')]
    list_names = [i for i in lines[1].split(',')]
    year = lines[2]
    dpi = 100
    fig_width = 5000 / dpi  # Width in inches
    fig_height = 800 / dpi  # Height in inches
    plt.figure(figsize=(fig_width,fig_height),dpi=dpi)
    bars = plt.bar(list_names, list_profit)
    bars[0].set_color('green');
    plt.xlabel('Departments')
    plt.ylabel('Profit (10000 DA)')
    plt.ticklabel_format(style='plain', axis='y')
    plt.title("Top Departments performance wise in "+year)
    plt.show()