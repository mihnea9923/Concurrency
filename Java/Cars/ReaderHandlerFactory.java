package com.apd.tema2.factory;

import java.io.BufferedReader;
import java.io.IOException;

import com.apd.tema2.Main;
import com.apd.tema2.entities.ReaderHandler;

/**
 * Returneaza sub forma unor clase anonime implementari pentru metoda de citire
 * din fisier.
 */
public class ReaderHandlerFactory {

	public static ReaderHandler getHandler(String handlerType) {
		// simple semaphore intersection
		// max random N cars roundabout (s time to exit each of them)
		// roundabout with exactly one car from each lane simultaneously
		// roundabout with exactly X cars from each lane simultaneously
		// roundabout with at most X cars from each lane simultaneously
		// entering a road without any priority
		// crosswalk activated on at least a number of people (s time to finish all of
		// them)
		// road in maintenance - 1 lane 2 ways, X cars at a time
		// road in maintenance - N lanes 2 ways, X cars at a time
		// railroad blockage for T seconds for all the cars
		// unmarked intersection
		// cars racing
		ReaderHandler handler;
		switch (handlerType) {
		case "simple_semaphore" : handler = new ReaderHandler() {
			@Override
			public void handle(final String handlerType, final BufferedReader br) {
				// Exemplu de utilizare:
				Main.intersection = IntersectionFactory.getIntersection("simple_semaphore");
			}
		};
		case "simple_n_roundabout" : handler = new ReaderHandler() {
			@Override
			public void handle(final String handlerType, final BufferedReader br) throws IOException {
				// To parse input line use:
				// String[] line = br.readLine().split(" ");
			}
		};
		case "simple_strict_1_car_roundabout" : handler = new ReaderHandler() {
			@Override
			public void handle(final String handlerType, final BufferedReader br) throws IOException {

			}
		};
		case "simple_strict_x_car_roundabout" : handler = new ReaderHandler() {
			@Override
			public void handle(final String handlerType, final BufferedReader br) throws IOException {

			}
		};
		case "simple_max_x_car_roundabout" : handler = new ReaderHandler() {
			@Override
			public void handle(final String handlerType, final BufferedReader br) throws IOException {

			}
		};
		case "priority_intersection" : handler = new ReaderHandler() {
			@Override
			public void handle(final String handlerType, final BufferedReader br) throws IOException {

			}
		};
		case "crosswalk" : handler = new ReaderHandler() {
			@Override
			public void handle(final String handlerType, final BufferedReader br) throws IOException {

			}
		};
		case "simple_maintenance" : handler = new ReaderHandler() {
			@Override
			public void handle(final String handlerType, final BufferedReader br) throws IOException {

			}
		};
		case "complex_maintenance" : handler = new ReaderHandler() {
			@Override
			public void handle(final String handlerType, final BufferedReader br) throws IOException {

			}
		};
		case "railroad" : handler = new ReaderHandler() {
			@Override
			public void handle(final String handlerType, final BufferedReader br) throws IOException {

			}
		};
		default : handler = null;
		};
		return handler;
	}

}
