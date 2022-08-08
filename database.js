const mysql = require('mysql');
const connection = mysql.createPool({
  host: '127.0.0.1',
  user: 'netuser',
  password: 'netpass',
  database: 'netdb',
});
module.exports = connection;