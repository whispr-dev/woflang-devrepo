change to project directory:
`cd C:\Users\User\Desktop\analog_logic_lang\`


Create a Virtual Environment:
(mine is called `woflang_env`)

`python -m venv woflang_env`


 to Activate the Virtual Environment:

`woflang_env\Scripts\activate`

 

to install libraries:

`pip install -r requirements.txt`



#######


to Deactivate the Virtual Environment:

`deactivate`


Installing Packages:

`pip install matplotlib`


Finally run the Python script:

(woflang_env) PS C:\Users\User\Desktop\analog_logic_lang> python interpreter_for_woflang_v-0-0-4.py


- Listing Installed Packages:

`pip list`


fren can ou show me what format the contents of a venv requirements.txt should be in?


ChatGPT said:

Latest Version: If you want to install the latest version of a package, you can just list the package name:

```plaintext
requests
```

Comments: You can add comments to your requirements.txt file by starting a line with a #:

```plaintext
# This is a comment
requests==2.25.1
```


Automatically Generating requirements.txt

This format is what pip expects when you run:

```bash
pip install -r requirements.txt
```

This command will install all the packages listed in the file with the specified versions.

#######