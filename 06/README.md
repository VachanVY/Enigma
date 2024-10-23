# Assembler Logic in Pseudo-Code/Python

```python
class Assembler:
    def __init__(self, fname:str):
        with open(fname, mode="r") as f:
            self.lines = f.readlines()
        self.get_dest_comp_jump_symbols_table()
        
    def parse(self, lines:list[str]):
        # labels: equal to below line numbers
        # variables: is an int, starts from 16
        prepro_lines:list[str] = []
        line_count, var_start = 0, 16
        for line in lines:
            line = line.strip().split("//")[0].replace(" ", "") # // hi this a comment => ""
            if line == "": # skip empty lines
                continue
            elif line.startswith("(") and line.endswith(")"): # (LABEL)
                label = line[1:-1]
                self.symbols_table[label] = str(line_count)
                continue
            elif (
                line.startswith("@") and            # A-instruction
                not line[1:].isnumeric() and        # if not numeric no need to add in symbols table
                (not line[1:].isupper() and         # all char upper means it's a label
                line[1:] not in self.symbols_table) # but SCREEN, etc is not a label, it's given var, so no need
            ): # @var
                var = line[1:]
                self.symbols_table[var] = str(var_start)
                var_start+=1
            prepro_lines.append(line)
            line_count += 1
        return prepro_lines
    
    def __call__(self):
        binary_form = ""
        preprocessed = self.parse(self.lines)
        for line in preprocessed:
            if line.startswith("@"):
                binary_line = self.handle_a_instruction(line)
            else:
                binary_line = self.handle_c_instruction(line)
            binary_form += (binary_line+"\n")
        return binary_form
        # self.see=dict(zip(range(len(preprocessed)), preprocessed))
    
    def handle_a_instruction(self, line:str):
        # line: @i or @2222
        address = line[1:]
        if address in self.symbols_table:
            address = self.symbols_table[address]
        return '0' + Assembler.get_binary_form(int(address), num_bits=15)

    def handle_c_instruction(self, line:str):
        """```
        dest=comp;jump # has_dest and has_jump
            OR
        comp;jump      # has_jump
            OR
        dest=comp      # has_dest
        ```"""
        has_jump = ";" in line
        has_dest = "=" in line

        dest, comp, jump = "", "", ""
        if has_dest and has_jump:
            dest_comp, jump = line.split(";")
            dest, comp = dest_comp.split("=")
        elif has_jump:
            comp, jump = line.split(";")
        elif has_dest:
            dest, comp = line.split("=")
        
        a_bit, cccccc_bits = self.comp_dict[comp]
        dest_bits = self.dest_dict[dest]
        jump_bits = self.jump_dict[jump]
        return "111" + (a_bit + cccccc_bits) + dest_bits + jump_bits
    
    @staticmethod
    def get_binary_form(uint:int, num_bits:int):
        return format(uint, f'0{num_bits}b')
    
    def get_dest_comp_jump_symbols_table(self):
        self.dest_dict = {
            "": "000",
            "M": "001",
            "D": "010",
            "MD": "011",
            "A": "100",
            "AM": "101",
            "AD": "110",
            "AMD": "111"
        }

        self.comp_dict = {
            "0": ("0", "101010"),
            "1": ("0", "111111"),
            "-1": ("0", "111010"),
            "D": ("0", "001100"),
            "A": ("0", "110000"),
            "!D": ("0", "001101"),
            "!A": ("0", "110001"),
            "-D": ("0", "001111"),
            "-A": ("0", "110011"),
            "D+1": ("0", "011111"),
            "A+1": ("0", "110111"),
            "D-1": ("0", "001110"),
            "A-1": ("0", "110010"),
            "D+A": ("0", "000010"),
            "D-A": ("0", "010011"),
            "A-D": ("0", "000111"),
            "D&A": ("0", "000000"),
            "D|A": ("0", "010101"),
            "M": ("1", "110000"),
            "!M": ("1", "110001"),
            "-M": ("1", "110011"),
            "M+1": ("1", "110111"),
            "M-1": ("1", "110010"),
            "D+M": ("1", "000010"),
            "D-M": ("1", "010011"),
            "M-D": ("1", "000111"),
            "D&M": ("1", "000000"),
            "D|M": ("1", "010101")
        }

        self.jump_dict = {
            "": "000",
            "JGT": "001",
            "JEQ": "010",
            "JGE": "011",
            "JLT": "100",
            "JNE": "101",
            "JLE": "110",
            "JMP": "111"
        }

        self.symbols_table = {
            "R0": "0",
            "R1": "1",
            "R2": "2",
            "R3": "3",
            "R4": "4",
            "R5": "5",
            "R6": "6",
            "R7": "7",
            "R8": "8",
            "R9": "9",
            "R10": "10",
            "R11": "11",
            "R12": "12",
            "R13": "13",
            "R14": "14",
            "R15": "15",
            "SCREEN": "16384",
            "KBD": "24576",
            "SP": "0",
            "LCL": "1",
            "ARG": "2",
            "THIS": "3",
            "THAT": "4",
        }
```
