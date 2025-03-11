# Food-Spoilage-Monitoring-System

## Overview
The **Food Spoilage Monitoring System** is designed to monitor environmental conditions during the transportation of perishable goods, such as bananas. The system aims to reduce food waste and minimize business losses by providing real-time data on temperature, humidity, and ethylene gas levels.

## Features
- Real-time monitoring of temperature, humidity, and ethylene gas.
- Automated alerts using LEDs, buzzers, and email notifications.
- Data visualization via the Arduino IoT Cloud Dashboard and a mobile app.
- Data storage and analysis through Google Sheets.
- Automated air ventilation control using a servo motor.

## Problem Statement
Perishable fruits like bananas release ethylene gas when exposed to environmental factors such as temperature and humidity, which accelerates spoilage. Without proper monitoring, businesses face:
- Increased food waste due to unnoticed spoilage.
- Difficulty maintaining optimal storage conditions.
- Delays in timely delivery due to reliance on manual checks.

## Solution
This project utilizes the **Arduino MKR 1010** microcontroller along with key sensors to track real-time environmental conditions. When critical thresholds are exceeded, the system triggers alerts and transmits data to the cloud for stakeholders to take immediate action.

## Components Used
- **Arduino MKR 1010** – Microcontroller with built-in Wi-Fi for IoT functionality.
- **MQ4 Gas Sensor** – Detects ethylene gas emissions from perishable foods.
- **Temperature & Humidity Sensors** – Measures storage conditions.
- **Servo Motor** – Controls air ventilation to regulate gas and humidity levels.
- **LED & Buzzer** – Provides visual and auditory alerts.
- **Google Sheets & Arduino IoT Cloud Dashboard** – Stores and displays real-time data.

## How It Works
1. Sensors collect temperature, humidity, and gas level data in real-time.
2. The data is displayed locally on the MKR screen and remotely via the IoT Cloud.
3. If a threshold is exceeded:
   - LEDs and buzzers activate.
   - The MKR display status changes from *Normal* to *Risk*.
   - An automated email alert is sent to stakeholders.
   - The servo motor adjusts ventilation for improved air circulation.
4. All data is transmitted to Google Sheets for future analysis and decision-making.

## Departments Involved
- **Supply Chain Management**: Tracks ethylene gas emissions and prevents spoilage.
- **Quality Control**: Ensures optimal storage conditions to prevent mold and decay.
- **Logistics & Transportation**: Uses real-time data to optimize delivery schedules.

## Installation & Setup
1. Connect the sensors and components to the **Arduino MKR 1010**.
2. Upload the provided Arduino code to the microcontroller.
3. Configure the Arduino IoT Cloud Dashboard for remote monitoring.
4. Set up Google Apps Scripts for data transmission to Google Sheets.
5. Run tests to validate the system’s accuracy and response time.

## Future Enhancements
- Integration with AI for predictive analytics on spoilage trends.
- GPS tracking to correlate spoilage data with location.
- Expansion to monitor additional perishable food categories.

## References
- [Arduino MKR 1010 Guide](https://www.arduino.cc/en/Guide/MKR1010)
- [Supply Chain Management for Perishable Products](https://mpra.ub.uni-muenchen.de/119231/1/MPRA%20paper%20119193.pdf)
- [Gas Sensing in Food Quality Detection](https://doi.org/10.3390/foods12213966)

---
**Author:** Zeeshan Haider  
**University:** Hof University of Applied Sciences  
**Course:** Software Engineering for Industrial Applications  
**Instructor:** Prof. Dr. Heike Markus  
**Date:** January 15, 2025

