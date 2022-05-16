# CS50 Transit
#### Video Demo:  https://youtu.be/Nkv9DXlchH0
#### Description:
My project is a website that takes as input an origin and a destination, and from that will use the Google Maps API to get a distance for varying
modes of transportation. Using those results, the program will then calculate CO2 emissions for each mode using researched values. It will also
include a link to directions on google maps. The site is styled based on CS50 finance, and I would like to add more advanced features such as
obtaining current location, showing more accurate CO2 emission results, showing a map of options and including location suggestions in the future.



The App.py file does the bulk of the work, where it will get the data from the submitted form and then send it to the Google Maps API to process a
distance travelled for each method used. Finally, it will use those distance values in combination with a multiplier to calculate a CO2 emissions
profile, which is then passed to the HTML template. Unfortunately the distance data provided by google maps for rail/bus modes is often the same as
they use the same route, meaning that CO2 emissions will be inaccurate. This is something I am looking into fixing, but for now there will be a note
explaining the possible inaccuracies present. If the directions cannot be calculated because there is not a route between the two locations, or the
two locations don’t exist, then an error message is displayed.




Apology.html essentially just displays an error message that is provided by App.py



index.html displays the form for entering in details of each location and submitting it



layout.html contains details for the header and footer files with references and displays the favicon. I decided to mostly reuse the design from the
CS50 finance as it is simple, yet delivers the purpose required beautifully. I will likely update the design in the future, though.



response.html takes the data and displays it in a well-formatted table. I would have liked to show this in a cooler method but ran out of time. It
also displays the url to access the google maps icon. The table is formatted in a way that can easily be read by hovering with a mouse over each row



styles.css describes the colour for the top text


I hope in the future to use the data provided by the API to calculate emissions for each leg of a transit journey to increase accuracy. I would also
 like to show a map on the home-screen, so it is more transit planner like. I would also like to have a friendlier interface for displaying the info, such as by using icons and colours, as well as maybe graphs, and incorperate showing the directions directly in the details as well. Also, id like to add flight data to compare, and show overall time of travel to compare that as well. 