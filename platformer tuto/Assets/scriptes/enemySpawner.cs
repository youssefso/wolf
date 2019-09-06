using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class enemySpawner : MonoBehaviour {

	// Use this for initialization
	public GameObject enemy;
	public float spawntime;

	void Start () {
		InvokeRepeating("Spawn", spawntime, spawntime);
	}
	
	// Update is called once per frame
	void Update () {
		
	}

	private void Spawn()
	{
		Vector3 position = new Vector3 (Random.Range(-10,10), Random.Range(-4,4), 0);
		Instantiate(enemy, position, Quaternion.identity);
	}
}
