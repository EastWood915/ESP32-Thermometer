function displayTemperature(temperature)
{
    console.log("Temperature: " + temperature)
}

fetch('https://dweet.io/get/latest/dweet/for/jbdhsuk')
  .then(response => response.json())
  .then(data => displayTemperature(data.with[0].content.temperature));


