const TEMP_OFFSET = 7;
const TEMP_COEF = 1;

function displayTemperature(data)
{
    console.log(data);

    let temperature = data.with[0].content.temperature;
    let date = new Date(data.with[0].created);
    
    temperature = TEMP_COEF * temperature + TEMP_OFFSET;

    document.querySelector("span.spinner-border").style.visibility = "hidden";
    document.querySelector("h1.temperature").textContent = temperature.toFixed(1) + "°C";
    document.querySelector("span.date").textContent = date.toLocaleDateString("pl-PL", {weekday: 'long', day: 'numeric', month: 'long', year: 'numeric', hour: 'numeric', minute: 'numeric', second: 'numeric'});
    document.querySelector("span.date").style.visibility = "visible";
}

fetch('https://dweet.io/get/latest/dweet/for/jbdhsuk')
  .then(response => response.json())
  .then(data => displayTemperature(data));

