function displayTemperature(data)
{
    console.log(data);

    let temperature = data.with[0].content.temperature;
    let date = new Date(data.with[0].created);

    document.querySelector("span.spinner-border").style.visibility = "hidden";
    document.querySelector("h1.temperature").textContent = temperature + "°C";
    document.querySelector("span.date").textContent = date.toLocaleDateString("pl-PL", {weekday: 'long', day: 'numeric', month: 'long', year: 'numeric', hour: 'numeric', minute: 'numeric', second: 'numeric'});
    document.querySelector("span.date").style.visibility = "visible";
}

fetch('https://dweet.io/get/latest/dweet/for/jbdhsuk')
  .then(response => response.json())
  .then(data => displayTemperature(data));

