import os

def main():
    files = [f for f in os.listdir('.') if os.path.isfile(f)]
    logs = ""
    print(files)
    for f in files: 
        if "Logs" in f:
            logs = f
            break
    logs = logs + "/Movements"
    print("Running Script: " + logs)

if __name__ == "__main__":
    main()

