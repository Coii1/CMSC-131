def main() -> None:
    initial_balance: int = int(input("Input initial balance in centavos: "))
    interest: int = int(input("Input interest in fixed-point decimal: "))
    years: int = int(input("Input number of years: "))
    
    current_balance = initial_balance
    
    for year in range(1, years + 1):
        interest_amount = (current_balance * interest) // 10000
        
        current_balance += interest_amount
        
        print(f"Year: {year} -> Balance: ", end="")
        
        dollars = current_balance // 100
        cents = current_balance % 100
        
        print(f"{dollars}.{cents:02d}")
    
if __name__ == "__main__":
    main()