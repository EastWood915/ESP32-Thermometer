function displayTemperature(data)
{
    console.log(data);

    let temperature = data.with[0].content.temperature;
    let date = data.with[0].created;

    document.querySelector("span.spinner-border").style.visibility = "hidden";
    document.querySelector("h1.temperature").textContent = temperature + "°C";
    document.querySelector("span.date").textContent = date.replace('T', ' ').slice(0,-5);
    document.querySelector("span.date").style.visibility = "visible";
}

fetch('https://dweet.io/get/latest/dweet/for/jbdhsuk')
  .then(response => response.json())
//  .then(data => displayTemperature(data.with[0].content.temperature));
  .then(data => displayTemperature(data));

