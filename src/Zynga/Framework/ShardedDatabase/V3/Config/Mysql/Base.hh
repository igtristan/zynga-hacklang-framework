<?hh // strict

namespace Zynga\Framework\ShardedDatabase\V3\Config\Mysql;

use Zynga\Framework\ShardedDatabase\V3\Config\Base as ConfigShardedBase;
use Zynga\Framework\ShardedDatabase\V3\ConnectionDetails;
use Zynga\Framework\ShardedDatabase\V3\Driver\GenericPDO\Quoter;
use Zynga\Framework\ShardedDatabase\V3\Driver\GenericPDO\Transaction;
use Zynga\Framework\ShardedDatabase\V3\Info as ShardInfo;
use Zynga\Framework\ShardedDatabase\V3\Interfaces\DriverInterface;
use Zynga\Framework\ShardedDatabase\V3\Interfaces\QuoteInterface;
use Zynga\Framework\ShardedDatabase\V3\Interfaces\TransactionInterface;
use Zynga\Framework\Type\V1\Interfaces\TypeInterface;

abstract class Base<TType as TypeInterface> extends ConfigShardedBase<TType> {
  
  public function getDriver(): string {
    return 'GenericPDO';
  }

  public function getConnectionStringForServer(
    TType $intShardType,
    ConnectionDetails $server,
  ): string {
    $database = $this->getDatabaseName();
    $hostname = $server->getHostname();
    $port = $server->getPort();
    $this->setCurrentDatabase($database);
    $this->setCurrentServer($hostname);
    $dsn = '';
    $dsn = 'mysql:host='.$hostname.';dbname='.$database.';'.$port;
    return $dsn;
  }

  public function getServerFromShardType(TType $shardType): ConnectionDetails {
    $shardIndex = $this->getShardId($shardType);
    return $this->getServerByOffset($shardIndex);
  }
}