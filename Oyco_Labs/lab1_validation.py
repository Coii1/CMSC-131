ROWS: int = 1000

def main() -> None:
    def celsius_to_fahrenheit(celsius: int) -> int:
        return int((celsius * 9) // 5 + 32)

    def fahrenheit_to_kelvin(fahrenheit: int) -> int:
        return int((fahrenheit - 32) * 5 // 9 + 273)

    def kelvin_to_celsius(kelvin: int) -> int:
        return kelvin - 273

    print("Celsius | Fahrenheit | Kelvin | Final Celsius")
    print("-" * 45)
    for i in range(0, ROWS + 1):
        fahrenheit = celsius_to_fahrenheit(i)
        kelvin = fahrenheit_to_kelvin(fahrenheit)
        final_celsius = kelvin_to_celsius(kelvin)
        
        print(f"{i:7} | {fahrenheit:10} | {kelvin:6} | {final_celsius:13}")

if __name__ == "__main__":
    main()