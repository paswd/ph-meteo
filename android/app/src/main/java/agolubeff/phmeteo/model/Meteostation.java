package agolubeff.phmeteo.model;

public class Meteostation
{
    private String name;
    private int temperature;
    private int time;
    private int humidity;
    private int atmosphere_pressure;

    public Meteostation(String name, int temperature, int time, int humidity, int atmosphere_pressure)
    {
        this.name = name;
        this.temperature = temperature;
        this.time = time;
        this.humidity = humidity;
        this.atmosphere_pressure = atmosphere_pressure;
    }

    public String GetName()
    {
        return name;
    }

    public int GetTemperature()
    {
        return temperature;
    }

    public int GetTime()
    {
        return time;
    }

    public int GetHumidity()
    {
        return humidity;
    }

    public int GetAtmospherePressure()
    {
        return atmosphere_pressure;
    }
}
