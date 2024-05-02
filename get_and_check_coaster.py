import requests
from bs4 import BeautifulSoup

# URL of the webpage
url = "https://www.cs.virginia.edu/~jrh4az/wiotfinal.html"

# Send a GET request to the webpage
response = requests.get(url)

# Check if the request was successful (status code 200)
if response.status_code == 200:
    # Parse the HTML content
    soup = BeautifulSoup(response.text, 'html.parser')
    
    # Find the input element by its ID
    input_element = soup.find(id="coasterNumber")
    
    # Get the value of the input element
    coaster_number = input_element["value"]
    
    # Print the coaster number
    print("Coaster number:", coaster_number)
else:
    print("Failed to fetch the webpage")
