<?php
 
/**
 * @author Ravi Tamada
 * @link https://www.androidhive.info/2012/01/android-login-and-registration-with-php-mysql-and-sqlite/ Complete tutorial
 */
 
class DB_Functions {
 
    private $conn;
 
    // constructor
    function __construct() {
        require_once 'DB_Connect.php';
        // connecting to database
        $db = new Db_Connect();
        $this->conn = $db->connect();
    }
 
    // destructor
    function __destruct() {
         
    }
 
    /**
     * Storing new meteo data
     * returns meteo details
     */
    public function storeMeteo($id_stat, $unic_id, $temperature, $humidity, $atmosphere_pressure, $altitude) {
        $current_time = date("U");
        $this->conn->query("INSERT INTO `meteostation_data`
            VALUES(NULL, $id_stat, $current_time, $temperature, $humidity, $atmosphere_pressure, $altitude, '')") or die(mysqli_error($this->conn));

        $res = $this->conn->query("SELECT * FROM `meteostation_data` WHERE `unic_id` = $id_stat AND `time` = $current_time") or die(mysqli_error($this->conn));
        return $res->num_rows;
    }

    /**
     * Determine the station serial number
     */
    public function stationNumber($unic_id) {
	    $stmt = $this->conn->prepare("SELECT id from meteostations WHERE unic_id = ?");
	    $stmt->bind_param("s", $unic_id);
	    $stmt->execute();
        $result = $stmt->get_result()->fetch_assoc();
	    $stmt->close();
        $result = (int) $result;
        if ($result) {
            return $result;
        } else {
            return false;
        }
    }

    /**
     * Registration meteostations
     */

    public function registerNewStation($unic_id) {
        $result = $this->conn->query("INSERT INTO `meteostations` (`unic_id`) VALUES(\"$unic_id\")") or die(mysqli_error($this->conn));

        //check for successful registration
        if ($result) {
            $station = $this->conn->query("SELECT * FROM `meteostations` WHERE `unic_id` = \"$unic_id\"") or die(mysqli_error($this->conn));
            return $station->num_rows;
        } else {
            return false;
        }
    }

    /**
     * Check station is existed or not
     */ 

    public function isStationExisted($unic_id) {
        $stmt = $this->conn->prepare("SELECT unic_id FROM meteostations WHERE unic_id = ?");

        $stmt->bind_param("s", $unic_id);
        $stmt->execute();
 
        $stmt->store_result();
        if ($stmt->num_rows > 0) {
            //station existed
            $stmt->close();
            return true;
        } else {
            //station not existed
            $stmt->close();
            return false;
        }
    }

    /**
     * Timeout value
     */

    public function isTimeout($unic_id) {
        $stmt = $this->conn->prepare("SELECT timeout FROM meteostations WHERE unic_id = ?");
        $stmt->bind_param("s", $unic_id);
        $stmt->execute();
        $timeout = $stmt->get_result()->fetch_assoc();
        $stmt->close();
        return $timeout;
    }
}
?>