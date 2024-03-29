<?php
require_once 'include/DB_Functions.php';
//require_once 'include/CryptKeys.php';

$response = array("error" => FALSE);

function InsertData($db) {
	if (isset($_GET['unic_id']) && isset($_GET['temperature']) && isset($_GET['humidity'])
			&& isset($_GET['altitude']) && isset($_GET['atmosphere_pressure'])) {
		//receiving the meteo params
		$unic_id = htmlspecialchars($_GET['unic_id']);
		$temperature = $_GET['temperature'];
		$humidity = $_GET['humidity'];
		$atmosphere_pressure = $_GET['atmosphere_pressure'];
		$altitude = $_GET['altitude'];
		settype($temperature, "integer");
		settype($humidity, "integer");
		settype($atmosphere_pressure, "integer");
		settype($altitude, "integer");

		//found id station
		$id_stat = $db->stationNumber($unic_id);
		if ($id_stat) {
			//transform to numeric type
			$temperature = (int) $temperature;
			$humidity = (int) $humidity;
			$atmosphere_pressure = (int) $atmosphere_pressure;

			//insert meteo data
			$date = $db->storeMeteo($id_stat, $unic_id, $temperature, $humidity, $atmosphere_pressure, $altitude);
			if ($date) {
				//data was insert
				$response["error"] = FALSE;
				$response["id_stat"] = $date["id"];
				$response["date"]["unic_id"] = $date["unic_id"];
				$response["date"]["temperature"] = $date["temperature"];
				$response["date"]["humidity"] = $date["humidity"];
				$response["date"]["atmosphere_pressure"] = $date["atmosphere_pressure"];
				return 0;
			} else {
				//unexpected error (code 1)
				$response["error"] = TRUE;
				$response["error_msg"] = "Unexpected error. Code 1";
				return 500;
			}
		} else {
			$response["error"] = TRUE;
			$response["error_msg"] = "The station was not found";
			return 1;
		}
	} else {
		// required params is missing
	    $response["error"] = TRUE;
	    $response["error_msg"] = "Required parameters (temperature, humidity or atmosphere pressure) is missing!";
	    return 2;
	}
}

function Registration($db) {
	if (isset($_GET['unic_id'])) {
		$machine_id = $_GET['unic_id']; 
		$protected_id = htmlspecialchars($machine_id);

		//create new station
		$station = $db->registerNewStation($protected_id); 
		if ($station) {
			return 0;
		} else {
			return 500;
		}
	} else {
		return 1;
	}
}

function CheckStat($db) {
	if (isset($_GET['unic_id'])) {
		$machine_id = $_GET['unic_id']; 
		$protected_id = htmlspecialchars($machine_id);

		$station = $db->isStationExisted($protected_id);
		if ($station) {
			//station found
			$res = $db->isTimeout($protected_id);
			$response["error"] = FALSE;
			$response["error_msg"] = "Station  found";
			return $res["timeout"];
		} else {
			//station not found
			$response["error"] = TRUE;
			$response["error_msg"] = "Station not found";
			return -1;
		}

	}
}

function TestFunction($db) {
	$res = CheckStat($db);
	foreach ($res as $key=>$value) {
		echo $key.":".$value."<br>";
	}
}

$db = new DB_Functions();

switch ($_GET["type"]) {
	case "data":
		echo InsertData($db);
		break;
	case "registration":
		echo Registration($db);
		break;
	case "check":
		echo CheckStat($db);
		break;
	case "test":
		echo TestFunction($db);
		break;
	default:
		echo "Incorrect query type";
		break;
}
?>