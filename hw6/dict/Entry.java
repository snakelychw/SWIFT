/* Entry.java */

package dict;
import list.*;
/**
 *  A class for dictionary entries.
 *
 *  DO NOT CHANGE THIS FILE.  It is part of the interface of the
 *  Dictionary ADT.
 **/

public class Entry {

  protected Object key;
  protected Object value;

  public Object key() {
    return key;
  }

  public Object value() {
    return value;
  }
  
  public Entry(Object k, Object v){
	  key = k;
	  value = v;
  }

}
