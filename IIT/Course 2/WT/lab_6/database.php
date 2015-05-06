<?php

/**
 * User: alkuk
 * Date: 01.04.15
 * Time: 16:26
 */

class Lab4DBManager
{
    public function __construct($host, $port, $db, $user, $password)
    {
        $this->last_result = null;
        $this->host = $host;
        $this->port = $port;
        $this->db = $db;
        $this->user = $user;
        $this->password = $password;
        $this->connection = mysql_pconnect($this->host.':'.$this->port, $user, $password);
        mysql_set_charset('utf8', $this->connection);
        mysql_select_db($db, $this->connection);

    }

    public function getMenuElements($parent = null)
    {
        $sql = 'SELECT * FROM `pages`';

        if ($parent) {
            $sql .= ' WHERE parent_id = '.$parent;
        } else {
            $sql .= ' WHERE parent_id IS NULL';
        }

        return $this->query($sql)->getAssocResult();
    }

    public function getLatestNews($count = 10)
    {
        $sql = 'SELECT * FROM `news` ORDER BY created DESC LIMIT 0,'.$count;

        return $this->query($sql)->getAssocResult();
    }

    public function query($sql)
    {
        $this->last_result = mysql_query($sql, $this->connection);

        return $this;
    }

    public function getAssocResult()
    {
        $data = array();
        while ($row = mysql_fetch_array($this->last_result, MYSQL_ASSOC)) {
            $data[] = $row;
        }

        return $data;
    }
}
